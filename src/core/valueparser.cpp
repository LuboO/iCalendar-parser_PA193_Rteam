#include "core/valueparser.h"

#include "parserexception.h"

#include <regex>
#include <climits>

namespace ical {
namespace core {

bool ValueParser::parseBoolean(const StreamPos &pos,
                               std::string::const_iterator begin,
                               std::string::const_iterator end)
{
    if (std::string(begin, end) == "TRUE") {
        return true;
    } else if (std::string(begin, end) == "FALSE") {
        return false;
    } else {
        throw ParserException(pos, "Invalid boolean value!");
    }
}

double ValueParser::parseFloat(const StreamPos &pos,
                               std::string::const_iterator begin,
                               std::string::const_iterator end)
{
    const std::regex RE_FLOAT { "([-+]?)([0-9]+)(:?.([0-9]+))" };
    if (!std::regex_match(begin, end, RE_FLOAT)) {
        throw ParserException(pos, "Invalid float value!");
    }
    /* the regex already ensures correct format for std::stof: */
    try {
        return std::stod(std::string(begin, end));
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Float value out of range for double!");
    }
}

int ValueParser::parseInteger(const StreamPos &pos,
                              std::string::const_iterator begin,
                              std::string::const_iterator end)
{
    const std::regex RE_INTEGER { "([-+]?)([0-9]+)" };
    if (!std::regex_match(begin, end, RE_INTEGER)) {
        throw ParserException(pos, "Invalid float value!");
    }
    /* the regex already ensures correct format for std::stoi: */
    try {
        return std::stoi(std::string(begin, end));
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Integer value out of range for int!");
    }
}

unsigned int ValueParser::parseUnsignedInteger(
        const StreamPos &pos,
        std::string::const_iterator begin,
        std::string::const_iterator end)
{
    const std::regex RE_UINTEGER { "([0-9]+)" };
    if (!std::regex_match(begin, end, RE_UINTEGER)) {
        throw ParserException(pos, "Invalid float value!");
    }
    /* the regex already ensures correct format for std::stou: */
    try {
        auto ul = std::stoul(std::string(begin, end));
        if (ul > UINT_MAX) {
            throw std::out_of_range("");
        }
        return static_cast<unsigned int>(ul);
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Unsigned integer value out of range for unsigned int!");
    }
}

std::string ValueParser::parseText(const StreamPos &pos,
                                   std::string::const_iterator begin,
                                   std::string::const_iterator end)
{
    std::string res;
    while (begin != end) {
        char c = *begin;
        if (c == ';' || c == ',') {
            throw ParserException(pos, "Invalid text character!");
        }
        if (c == '\\') {
            if (++begin == end) {
                throw ParserException(pos, "Incomplete escape sequence in text value!");
            }
            c = *begin;
            if (c == '\\' || c == ';' || c == ',') {
                res.push_back(c);
            } else if (c == 'n' || c == 'N') {
                res.push_back('\n');
            } else {
                throw ParserException(pos, "Invalid escape sequence in text value!");
            }
        } else {
            res.push_back(c);
        }
        ++begin;
    }
    return res;
}

std::string ValueParser::parseCalendarAddress(
        const StreamPos &pos,
        std::string::const_iterator begin,
        std::string::const_iterator end)
{
    return parseUri(pos, begin, end);
}

std::string ValueParser::parseUri(const StreamPos &,
                                  std::string::const_iterator begin,
                                  std::string::const_iterator end)
{
    // TODO: should we even validate this?
    return { begin, end };
}

static unsigned char base64value(const StreamPos &pos, char c)
{
    if (c >= 'A' && c <= 'Z') {
        return static_cast<unsigned char>(c - 'A');
    } else if (c >= 'a' && c <= 'z') {
        return static_cast<unsigned char>(c - 'a') + 26;
    } else if (c >= '0' && c <= '9') {
        return static_cast<unsigned char>(c - '0') + 2 * 26;
    } else if (c == '+') {
        return 2 * 26 + 10;
    } else if (c == '/') {
        return 2 * 26 + 10 + 1;
    } else {
        throw ParserException(pos, "Invalid base64 character!");
    }
}

static std::string base64decode(const StreamPos &pos,
                                std::string::const_iterator begin,
                                std::string::const_iterator end)
{
    auto inLength = static_cast<std::size_t>(end - begin);
    if (inLength % 4 != 0) {
        throw ParserException(pos, "Base64 sequence has invalid length!");
    }
    if (inLength == 0) {
        return {};
    }

    std::size_t outLength = (inLength / 4) * 3;
    std::size_t padding = 0;
    while (padding <= 2 && *(end - padding - 1) == '=') {
        ++padding;
    }
    outLength -= padding;

    std::string res;
    res.reserve(outLength);
    while (true) {
        unsigned long int val;
        for (std::size_t i = 0; i < 4; i++) {
            val <<= 6;
            if (static_cast<std::size_t>(end - begin) > padding) {
                val |= base64value(pos, *begin);
            }
            ++begin;
        }
        res.push_back(static_cast<char>((val >> 16) & 0xFF)); --outLength;
        if (outLength == 0) {
            break;
        }
        res.push_back(static_cast<char>((val >>  8) & 0xFF)); --outLength;
        if (outLength == 0) {
            break;
        }
        res.push_back(static_cast<char>((val >>  0) & 0xFF)); --outLength;
        if (outLength == 0) {
            break;
        }
    }
    return res;
}

std::string ValueParser::parseBase64(const StreamPos &pos,
                                     std::string::const_iterator begin,
                                     std::string::const_iterator end)
{
    return base64decode(pos, begin, end);
}

static unsigned int parseNumber(std::string::const_iterator it,
                                std::size_t digits)
{
    unsigned int num = 0;
    for (std::size_t i = 0; i < digits; i++) {
        num *= 10;
        num += *it - '0';
        ++it;
    }
    return num;
}

unsigned int getDaysInMonth(unsigned int year, unsigned int month)
{
    switch (month)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return year % 4 == 0 &&
                (year % 100 != 0 || year % 400 == 0)
                ? 29 : 28;
    default:
        return 31;
    }
}

static const std::size_t DATE_LENGTH = 8;
static const std::size_t TIME_LENGTH_MIN = 6;

static const std::size_t DATETIME_LENGTH_MIN = DATE_LENGTH + 1 + TIME_LENGTH_MIN;

data::Date ValueParser::parseDate(const StreamPos &pos,
                                  std::string::const_iterator begin,
                                  std::string::const_iterator end)
{
    const std::regex RE_DATE { "^([0-9]{4})([0-9]{2})([0-9]{2})$" };

    std::smatch m;
    if (!std::regex_match(begin, end, m, RE_DATE)) {
        throw ParserException(pos, "Invalid date value!");
    }
    auto year = parseNumber(m[1].first, 4);
    auto month = parseNumber(m[2].first, 2);
    auto day = parseNumber(m[3].first, 2);
    if (month < 1 || month > 12) {
        throw ParserException(pos, "Invalid month!");
    }
    if (day < 1 || day > getDaysInMonth(year, month)) {
        throw ParserException(pos, "Invalid day in month!");
    }
    return { year, month, day };
}

data::Time ValueParser::parseTime(const StreamPos &pos,
                                  std::string::const_iterator begin,
                                  std::string::const_iterator end)
{
    const std::regex RE_TIME { "^([0-9]{2})([0-9]{2})([0-9]{2})(Z?)$" };

    std::smatch m;
    if (!std::regex_match(begin, end, m, RE_TIME)) {
        throw ParserException(pos, "Invalid time value!");
    }

    auto hour = parseNumber(m[1].first, 2);
    auto minute = parseNumber(m[2].first, 2);
    auto second = parseNumber(m[3].first, 2);
    bool local = m[4].length() == 0;
    if (hour >= 24) {
        throw ParserException(pos, "Invalid hour!");
    }
    if (minute >= 60) {
        throw ParserException(pos, "Invalid minute!");
    }
    if (second >= 60) {
        throw ParserException(pos, "Invalid second!");
    }
    return { hour, minute, second, local };
}

data::DateTime ValueParser::parseDateTime(const StreamPos &pos,
                                          std::string::const_iterator begin,
                                          std::string::const_iterator end,
                                          bool timeIsOptional)
{
    if (static_cast<std::size_t>(end - begin) <
            DATE_LENGTH + (timeIsOptional ? 1 : 0)) {
        throw ParserException(pos, "Invalid datetime value!");
    }
    data::Date date = std::move(parseDate(pos, begin, begin + DATE_LENGTH));
    begin += DATE_LENGTH;
    if (timeIsOptional && begin == end) {
        return { std::move(date) };
    }
    /* If execution gets here, then either:
     * timeIsOptional == false (therefore total length is >= DATE_LENGTH + 1)
     * OR
     * timeIsOptional == true && begin != end  (end - begin >= 1)
     * In both cases, it is safe to read from begin here:
     */
    if (*begin != 'T') {
        throw ParserException(pos, "Invalid datetime value!");
    }
    data::Time time = std::move(parseTime(pos, begin + 1, end));
    return { std::move(date), std::move(time) };
}

data::UTCOffset ValueParser::parseUTCOffset(const StreamPos &pos,
                                            std::string::const_iterator begin,
                                            std::string::const_iterator end)
{
    const std::regex RE_UTC_OFFSET { "([+-])([0-9]{2})([0-9]{2})([0-9]{2})?" };
    std::smatch m;
    if (!std::regex_match(begin, end, m, RE_UTC_OFFSET)) {
        throw ParserException(pos, "Invalid UTC offset value!");
    }

    bool negative = *m[1].first == '-';
    unsigned int hours = parseNumber(m[2].first, 2);
    unsigned int minutes = parseNumber(m[3].first, 2);
    unsigned int seconds = m[4].matched ? parseNumber(m[4].first, 2) : 0;
    if (hours >= 24) {
        throw ParserException(pos, "Invalid hours!");
    }
    if (minutes >= 60) {
        throw ParserException(pos, "Invalid minutes!");
    }
    if (seconds >= 60) {
        throw ParserException(pos, "Invalid seconds!");
    }
    if (negative && hours == 0 && minutes == 0 && seconds == 0) {
        throw ParserException(pos, "Negative zero UTC offset is not allowed!");
    }
    return { negative, hours, minutes, seconds };
}

data::Duration ValueParser::parseDuration(const StreamPos &pos,
                                          std::string::const_iterator begin,
                                          std::string::const_iterator end)
{
    const std::regex RE_DURATION {
        "^([-+]?)P(?:"
            "(([0-9]+)D(T(?:"
                "(([0-9]+)H(([0-9]+)M(([0-9]+)S)?)?)"
            "|"
                "(([0-9]+)M(([0-9]+)S)?)"
            "|"
                "(([0-9]+)S)"
            "))?)"
        "|"
            "(T(?:"
                "(([0-9]+)H(([0-9]+)M(([0-9]+)S)?)?)"
            "|"
                "(([0-9]+)M(([0-9]+)S)?)"
            "|"
                "(([0-9]+)S)"
            "))"
        "|"
            "(([0-9]+)W)"
        ")$"
    };
    std::smatch m;
    if (!std::regex_match(begin, end, m, RE_DURATION)) {
        throw ParserException(pos, "Invalid duration value!");
    }

    /* If anyone knows of a better (simpler) way to do this,
     * I'd like to see it: ;) */
    bool negative = m[1].length() != 0 && *m[1].first == '-';
    unsigned int weeks = 0;
    unsigned int days = 0;
    unsigned int hours = 0;
    unsigned int minutes = 0;
    unsigned int seconds = 0;
    if (m[2].matched) {
        /* dur-date */
        days = parseUnsignedInteger(pos, m[3].first, m[3].second);
        if (m[4].matched) {
            /* dur-time */
            if (m[5].matched) {
                /* dur-hour */
                hours = parseUnsignedInteger(pos, m[6].first, m[6].second);
                if (m[7].matched) {
                    minutes = parseUnsignedInteger(pos, m[8].first, m[8].second);
                    if (m[9].matched) {
                        seconds = parseUnsignedInteger(pos, m[10].first, m[10].second);
                    }
                }
            } else if (m[11].matched) {
                /* dur-minute */
                minutes = parseUnsignedInteger(pos, m[12].first, m[12].second);
                if (m[13].matched) {
                    seconds = parseUnsignedInteger(pos, m[14].first, m[14].second);
                }
            } else if (m[15].matched) {
                /* dur-second */
                seconds = parseUnsignedInteger(pos, m[16].first, m[16].second);
            } else {
                /* this shouldn't happen... */
                throw std::logic_error("Application logic error (check stack trace)!");
            }
        }
    } else if (m[17].matched) {
        /* dur-time */
        if (m[18].matched) {
            /* dur-hour */
            hours = parseUnsignedInteger(pos, m[19].first, m[19].second);
            if (m[20].matched) {
                minutes = parseUnsignedInteger(pos, m[21].first, m[21].second);
                if (m[22].matched) {
                    seconds = parseUnsignedInteger(pos, m[23].first, m[23].second);
                }
            }
        } else if (m[24].matched) {
            /* dur-minute */
            minutes = parseUnsignedInteger(pos, m[25].first, m[25].second);
            if (m[26].matched) {
                seconds = parseUnsignedInteger(pos, m[27].first, m[27].second);
            }
        } else if (m[28].matched) {
            /* dur-second */
            seconds = parseUnsignedInteger(pos, m[29].first, m[29].second);
        } else {
            /* this shouldn't happen... */
            throw std::logic_error("Application logic error (check stack trace)!");
        }
    } else if (m[30].matched) {
        weeks = parseUnsignedInteger(pos, m[31].first, m[31].second);
    } else {
        /* this shouldn't happen... */
        throw std::logic_error("Application logic error (check stack trace)!");
    }
    return { negative, weeks, days, hours, minutes, seconds };
}

data::Period ValueParser::parsePeriod(const StreamPos &pos,
                                      std::string::const_iterator begin,
                                      std::string::const_iterator end)
{
    auto slash = std::find(begin, end, '/');
    /* second part (after the slash) must have at least one character: */
    if (end - slash < 2) {
        throw ParserException(pos, "Invalid period value!");
    }
    auto startTime = parseDateTime(pos, begin, slash);
    char firstCharOfSecondPart = *(slash + 1);
    if (firstCharOfSecondPart == '-' || firstCharOfSecondPart == '+' ||
            firstCharOfSecondPart == 'P') {
        auto duration = parseDuration(pos, slash + 1, end);
        return { std::move(startTime), std::move(duration) };
    } else {
        auto endTime = parseDateTime(pos, slash + 1, end);
        return { std::move(startTime), std::move(endTime) };
    }
}

static data::WeekdayNumber parseWeekdayNum(
        const StreamPos &pos,
        std::string::const_iterator begin,
        std::string::const_iterator end)
{
    const std::regex RE_WEEKDAYNUM { "([-+]?[0-9]{1,2}})?(SU|MO|TU|WE|TH|FR|SA)" };
    std::smatch m;
    if (!std::regex_match(begin, end, m, RE_WEEKDAYNUM)) {
        throw ParserException(pos, "Invalid numbered weekday!");
    }
    int number = 0;
    if (m[1].matched) {
        number = ValueParser::parseInteger(pos, m[1].first, m[1].second);
        if (number == 0 || number < -53 || number > 53) {
            throw ParserException(pos, "Invalid weekday number!");
        }
    }
    return { number, m[2].str() };
}

data::RecurrenceRule ValueParser::parseRecurrenceRule(
        const StreamPos &pos,
        std::string::const_iterator begin,
        std::string::const_iterator end)
{
    std::string freq {};

    bool limitSet = false;
    bool limitByCount {};
    data::DateTime until {};
    unsigned int count {};

    bool intervalSet = false;
    unsigned int interval = 1;

    std::vector<unsigned int> bySecond;
    std::vector<unsigned int> byMinute;
    std::vector<unsigned int> byHour;
    std::vector<data::WeekdayNumber> byDay;
    std::vector<int> byMonthDay;
    std::vector<int> byYearDay;
    std::vector<int> byWeekNumber;
    std::vector<int> byMonth;
    std::vector<int> bySetPos;

    bool weekStartSet = false;
    std::string weekStart { "MO" };

    std::string::const_iterator delimIt;
    std::string::const_iterator elemIt = begin;
    while (true) {
        delimIt = std::find(elemIt, end, ';');

        auto eqSignIt = std::find(elemIt, delimIt, '=');
        if (eqSignIt == delimIt) {
            throw ParserException(pos, "Invalid reccurence rule format!");
        }
        std::string name { elemIt, eqSignIt };
        if (name == "FREQ") {
            if (!freq.empty()) {
                throw ParserException(pos, "Frequency cannot be specified multiple times!");
            }

            static const std::regex RE_FREQ { "SECONDLY|MINUTELY|HOURLY|DAILY|WEEKLY|MONTHLY|YEARLY" };
            if (!std::regex_match(eqSignIt + 1, delimIt, RE_FREQ)) {
                throw ParserException(pos, "Invalid frequency value!");
            }
            freq.assign(eqSignIt + 1, delimIt);
        } else if (name == "UNTIL") {
            if (limitSet) {
                throw ParserException(pos, "UNTIL/COUNT cannot be specified multiple times!");
            }

            limitByCount = false;
            until = std::move(parseDateTime(pos, eqSignIt + 1, delimIt, true));

            limitSet = true;
        } else if (name == "COUNT") {
            if (limitSet) {
                throw ParserException(pos, "UNTIL/COUNT cannot be specified multiple times!");
            }

            limitByCount = true;
            count = parseUnsignedInteger(pos, eqSignIt + 1, delimIt);

            limitSet = true;
        } else if (name == "INTERVAL") {
            if (intervalSet) {
                throw ParserException(pos, "INTERVAL cannot be specified multiple times!");
            }

            interval = parseUnsignedInteger(pos, eqSignIt + 1, delimIt);
            if (interval == 0) {
                throw ParserException(pos, "INTERVAL value cannot be zero!");
            }

            intervalSet = true;
        } else if (name == "BYSECOND") {
            if (!bySecond.empty()) {
                throw ParserException(pos, "BYSECOND cannot be specified multiple times!");
            }

            bySecond = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                                parseUnsignedInteger, ','));

            if (bySecond.empty()) {
                throw ParserException(pos, "BYSECOND cannot be empty!");
            }

            for (unsigned int i : bySecond) {
                if (i > 60) {
                    throw ParserException(pos, "Invalid seconds value!");
                }
            }
        } else if (name == "BYMINUTE") {
            if (!byMinute.empty()) {
                throw ParserException(pos, "BYMINUTE cannot be specified multiple times!");
            }

            byMinute = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                                parseUnsignedInteger, ','));

            if (byMinute.empty()) {
                throw ParserException(pos, "BYMINUTE cannot be empty!");
            }

            for (unsigned int i : byMinute) {
                if (i > 59) {
                    throw ParserException(pos, "Invalid minutes value!");
                }
            }
        } else if (name == "BYHOUR") {
            if (!byHour.empty()) {
                throw ParserException(pos, "BYHOUR cannot be specified multiple times!");
            }

            byHour = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                              parseUnsignedInteger, ','));
            if (byHour.empty()) {
                throw ParserException(pos, "BYHOUR cannot be empty!");
            }

            for (unsigned int i : byHour) {
                if (i > 23) {
                    throw ParserException(pos, "Invalid hour value!");
                }
            }
        } else if (name == "BYDAY") {
            if (!byDay.empty()) {
                throw ParserException(pos, "BYDAY cannot be specified multiple times!");
            }

            byDay = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                             parseWeekdayNum, ','));
            if (byDay.empty()) {
                throw ParserException(pos, "BYDAY cannot be empty!");
            }
        } else if (name == "BYMONTHDAY") {
            if (!byMonthDay.empty()) {
                throw ParserException(pos, "BYMONTHDAY cannot be specified multiple times!");
            }

            byMonthDay = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                                  parseInteger, ','));
            if (byMonthDay.empty()) {
                throw ParserException(pos, "BYMONTHDAY cannot be empty!");
            }

            for (int i : byMonthDay) {
                if (i == 0 || i < -31 || i > 31) {
                    throw ParserException(pos, "Invalid month day value!");
                }
            }
        } else if (name == "BYYEARDAY") {
            if (!byYearDay.empty()) {
                throw ParserException(pos, "BYYEARDAY cannot be specified multiple times!");
            }

            byYearDay = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                                 parseInteger, ','));
            if (byYearDay.empty()) {
                throw ParserException(pos, "BYYEARDAY cannot be empty!");
            }

            for (int i : byYearDay) {
                if (i == 0 || i < -366 || i > 366) {
                    throw ParserException(pos, "Invalid year day value!");
                }
            }
        } else if (name == "BYWEEKNO") {
            if (!byWeekNumber.empty()) {
                throw ParserException(pos, "BYWEEKNO cannot be specified multiple times!");
            }

            byWeekNumber = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                                    parseInteger, ','));
            if (byWeekNumber.empty()) {
                throw ParserException(pos, "BYWEEKNO cannot be empty!");
            }

            for (int i : byWeekNumber) {
                if (i == 0 || i < -53 || i > 53) {
                    throw ParserException(pos, "Invalid week number value!");
                }
            }
        } else if (name == "BYMONTH") {
            if (!byMonth.empty()) {
                throw ParserException(pos, "BYMONTH cannot be specified multiple times!");
            }

            byMonth = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                               parseInteger, ','));
            if (byMonth.empty()) {
                throw ParserException(pos, "BYMONTH cannot be empty!");
            }

            for (int i : byMonth) {
                if (i == 0 || i < -12 || i > 12) {
                    throw ParserException(pos, "Invalid week number value!");
                }
            }
        } else if (name == "BYSETPOS") {
            if (!bySetPos.empty()) {
                throw ParserException(pos, "BYSETPOS cannot be specified multiple times!");
            }

            bySetPos = std::move(parseDelimited(pos, eqSignIt + 1, delimIt,
                                                parseInteger, ','));
            if (bySetPos.empty()) {
                throw ParserException(pos, "BYSETPOS cannot be empty!");
            }

            for (int i : bySetPos) {
                if (i == 0 || i < -366 || i > 366) {
                    throw ParserException(pos, "Invalid year day value!");
                }
            }
        } else if (name == "WKST") {
            if (weekStartSet) {
                throw ParserException(pos, "WKST cannot be specified multiple times!");
            }

            const std::regex RE_WEEKDAY { "SU|MO|TU|WE|TH|FR|SA" };
            if (!std::regex_match(begin, end, RE_WEEKDAY)) {
                throw ParserException(pos, "Invalid weekday!");
            }

            weekStart.assign(eqSignIt + 1, delimIt);
            weekStartSet = true;
        } else {
            throw ParserException(pos, "Invalid reccurence rule part name!");
        }

        if (delimIt == end) {
            break;
        }
        /* skip the delimiter: */
        elemIt = delimIt + 1;
    }

    if (freq.empty()) {
        throw ParserException(pos, "Frequency is mandatory in recurrence rule!");
    }

    if ((freq != "MONTHLY" && freq != "YEARLY") ||
            (freq == "YEARLY" && !byWeekNumber.empty())) {
        for (auto &wd : byDay) {
            if (wd.getWeekNumber() != 0) {
                throw ParserException(pos,
                                      "Week numbers must not be specified "
                                      "when frequency is not MONTHLY or "
                                      "YEARLY, or when frequency is YEARLY "
                                      "and the BYWEEKNO part is specified!");
            }
        }
    }
    if (!byMonthDay.empty() && freq == "WEEKLY") {
        throw ParserException(pos,
                              "The BYMONTHDAY part must not be specified "
                              "if frequency is WEEKLY!");
    }
    if (!byWeekNumber.empty() && freq != "YEARLY") {
        throw ParserException(pos,
                              "The BYWEEKNO part must not be specified "
                              "if frequency is not YEARLY!");
    }
    if (!byYearDay.empty() &&
            (freq == "DAILY" || freq == "WEEKLY" || freq == "MONTHLY")) {
        throw ParserException(pos,
                              "The BYYEARDAY part must not be specified "
                              "if frequency is DAILY, WEEKLY or MONTHLY!");
    }
    if (!bySetPos.empty() &&
            bySecond.empty() && byMinute.empty() && byHour.empty() &&
            byWeekNumber.empty() && byMonthDay.empty() && byYearDay.empty() &&
            byMonth.empty()) {
        throw ParserException(pos,
                              "The BYSETPOS part can only be specified "
                              "with another BYxxx part!");
    }

    data::RecurrenceRuleOptions opts {
        interval,
        std::move(bySecond), std::move(byMinute), std::move(byHour),
        std::move(byDay), std::move(byMonthDay), std::move(byYearDay),
        std::move(byWeekNumber), std::move(byMonth), std::move(bySetPos),
        std::move(weekStart)
    };

    if (!limitSet) {
        return { std::move(freq), std::move(opts) };
    }

    if (limitByCount) {
        return { std::move(freq), count, std::move(opts) };
    } else {
        return { std::move(freq), std::move(until), std::move(opts) };
    }
}

} // namespace core
} // namespace ical

