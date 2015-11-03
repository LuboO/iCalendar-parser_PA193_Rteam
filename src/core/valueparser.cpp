#include "core/valueparser.h"

#include "parserexception.h"

#include <regex>

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
    /* the regex already ensures correct format for std::stof: */
    try {
        return std::stoi(std::string(begin, end));
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Float value out of range for double!");
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

std::string ValueParser::parseUri(StreamPos,
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

std::string ValueParser::parseBinary(const StreamPos &pos,
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
        return year % 4 == 0 ? 29 : 28;
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
                                          std::string::const_iterator end)
{
    if (end - begin < static_cast<std::ptrdiff_t>(DATE_LENGTH + 1)) {
        throw ParserException(pos, "Invalid datetime value!");
    }
    data::Date date = std::move(parseDate(pos, begin, begin + DATE_LENGTH));
    if (*(begin + DATE_LENGTH) != 'T') {
        throw ParserException(pos, "Invalid datetime value!");
    }
    data::Time time = std::move(parseTime(pos, begin + DATE_LENGTH + 1, end));
    return { std::move(date), std::move(time) };
}

data::UTCOffset ValueParser::parseUTCOffset(const StreamPos &pos,
                                            std::string::const_iterator begin,
                                            std::string::const_iterator end)
{
    // TODO: finish this
    return {};
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
        days = parseNumber(m[3].first, m[3].length());
        if (m[4].matched) {
            /* dur-time */
            if (m[5].matched) {
                /* dur-hour */
                hours = parseNumber(m[6].first, m[6].length());
                if (m[7].matched) {
                    minutes = parseNumber(m[8].first, m[8].length());
                    if (m[9].matched) {
                        seconds = parseNumber(m[10].first, m[10].length());
                    }
                }
            } else if (m[11].matched) {
                /* dur-minute */
                minutes = parseNumber(m[12].first, m[12].length());
                if (m[13].matched) {
                    seconds = parseNumber(m[14].first, m[14].length());
                }
            } else if (m[15].matched) {
                /* dur-second */
                seconds = parseNumber(m[16].first, m[16].length());
            } else {
                /* this shouldn't happen... */
                throw std::logic_error("Application logic error (check stack trace)!");
            }
        }
    } else if (m[17].matched) {
        /* dur-time */
        if (m[18].matched) {
            /* dur-hour */
            hours = parseNumber(m[19].first, m[19].length());
            if (m[20].matched) {
                minutes = parseNumber(m[21].first, m[21].length());
                if (m[22].matched) {
                    seconds = parseNumber(m[23].first, m[23].length());
                }
            }
        } else if (m[24].matched) {
            /* dur-minute */
            minutes = parseNumber(m[25].first, m[25].length());
            if (m[26].matched) {
                seconds = parseNumber(m[27].first, m[27].length());
            }
        } else if (m[28].matched) {
            /* dur-second */
            seconds = parseNumber(m[29].first, m[29].length());
        } else {
            /* this shouldn't happen... */
            throw std::logic_error("Application logic error (check stack trace)!");
        }
    } else if (m[30].matched) {
        weeks = parseNumber(m[31].first, m[31].length());
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

data::RecurrenceRule ValueParser::parseRecurrenceRule(
        const StreamPos &pos,
        std::string::const_iterator begin,
        std::string::const_iterator end)
{
    // TODO: finish this
    return {};
}

} // namespace core
} // namespace ical

