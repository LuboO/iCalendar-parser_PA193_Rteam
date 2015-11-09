#include "recurrencerule.h"

#include "parserexception.h"
#include "core/valueparser.h"

#include <regex>
#include <algorithm>

namespace ical {
namespace data {

using ValueParser = core::ValueParser;

void WeekdayNumber::print(std::ostream &out) const
{
    if (optWeekNumber != 0) {
        out << optWeekNumber;
    }
    out << weekday;
}

template<class T>
struct PrintHelper
{
    static void print(std::ostream &out, const T &val)
    {
        out << val;
    }
};

template<>
struct PrintHelper<WeekdayNumber>
{
    static void print(std::ostream &out, const WeekdayNumber &val)
    {
        val.print(out);
    }
};

template<class T>
static void printList(std::ostream &out, const std::string name, const std::vector<T> list)
{
    if (list.empty()) {
        return;
    }

    out << ';' << name << '=';
    PrintHelper<T>::print(out, list.front());
    for (auto it = list.begin() + 1; it < list.end(); it++) {
        out << ',';
        PrintHelper<T>::print(out, *it);
    }
}

void RecurrenceRule::print(std::ostream &out) const
{
    out << "FREQ=" << freq;
    if (limited) {
        if (limitedByCount) {
            out << ";COUNT=" << count;
        } else {
            out << ";UNTIL=";
            until.print(out);
        }
    }
    out << ";INTERVAL=" << opts.getInterval();

    printList(out, "BYSECOND", opts.getBySecond());
    printList(out, "BYMINUTE", opts.getByMinute());
    printList(out, "BYHOUR", opts.getByHour());
    printList(out, "BYDAY", opts.getByDay());
    printList(out, "BYMONTHDAY", opts.getByMonthDay());
    printList(out, "BYYEARDAY", opts.getByYearDay());
    printList(out, "BYWEEKNO", opts.getByWeekNumber());
    printList(out, "BYMONTH", opts.getByMonth());
    printList(out, "BYSETPOS", opts.getBySetPos());

    out << ";WKST=" << opts.getWeekStart();
}

WeekdayNumber WeekdayNumber::parse(const StreamPos &pos,
                                   std::string::const_iterator begin,
                                   std::string::const_iterator end)
{
    static const std::regex RE_WEEKDAYNUM { "([-+]?[0-9]{1,2}})?(SU|MO|TU|WE|TH|FR|SA)" };
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

RecurrenceRule RecurrenceRule::parse(const StreamPos &pos,
                                     std::string::const_iterator begin,
                                     std::string::const_iterator end)
{
    std::string freq {};

    bool limitSet = false;
    bool limitByCount {};
    DateTime until {};
    unsigned int count {};

    bool intervalSet = false;
    unsigned int interval = 1;

    std::vector<unsigned int> bySecond;
    std::vector<unsigned int> byMinute;
    std::vector<unsigned int> byHour;
    std::vector<WeekdayNumber> byDay;
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
            until = std::move(DateTime::parse(pos, eqSignIt + 1, delimIt, true));

            limitSet = true;
        } else if (name == "COUNT") {
            if (limitSet) {
                throw ParserException(pos, "UNTIL/COUNT cannot be specified multiple times!");
            }

            limitByCount = true;
            count = ValueParser::parseUnsignedInteger(pos, eqSignIt + 1, delimIt);

            limitSet = true;
        } else if (name == "INTERVAL") {
            if (intervalSet) {
                throw ParserException(pos, "INTERVAL cannot be specified multiple times!");
            }

            interval = ValueParser::parseUnsignedInteger(pos, eqSignIt + 1, delimIt);
            if (interval == 0) {
                throw ParserException(pos, "INTERVAL value cannot be zero!");
            }

            intervalSet = true;
        } else if (name == "BYSECOND") {
            if (!bySecond.empty()) {
                throw ParserException(pos, "BYSECOND cannot be specified multiple times!");
            }

            bySecond = std::move(ValueParser::parseDelimited(
                                     pos, eqSignIt + 1, delimIt,
                                     ValueParser::parseUnsignedInteger, ','));

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

            byMinute = std::move(ValueParser::parseDelimited(
                                     pos, eqSignIt + 1, delimIt,
                                     ValueParser::parseUnsignedInteger, ','));

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

            byHour = std::move(ValueParser::parseDelimited(
                                   pos, eqSignIt + 1, delimIt,
                                   ValueParser::parseUnsignedInteger, ','));
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

            byDay = std::move(ValueParser::parseDelimited(
                                  pos, eqSignIt + 1, delimIt,
                                  WeekdayNumber::parse, ','));
            if (byDay.empty()) {
                throw ParserException(pos, "BYDAY cannot be empty!");
            }
        } else if (name == "BYMONTHDAY") {
            if (!byMonthDay.empty()) {
                throw ParserException(pos, "BYMONTHDAY cannot be specified multiple times!");
            }

            byMonthDay = std::move(ValueParser::parseDelimited(
                                       pos, eqSignIt + 1, delimIt,
                                       ValueParser::parseInteger, ','));
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

            byYearDay = std::move(ValueParser::parseDelimited(
                                      pos, eqSignIt + 1, delimIt,
                                      ValueParser::parseInteger, ','));
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

            byWeekNumber = std::move(ValueParser::parseDelimited(
                                         pos, eqSignIt + 1, delimIt,
                                         ValueParser::parseInteger, ','));
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

            byMonth = std::move(ValueParser::parseDelimited(
                                    pos, eqSignIt + 1, delimIt,
                                    ValueParser::parseInteger, ','));
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

            bySetPos = std::move(ValueParser::parseDelimited(
                                     pos, eqSignIt + 1, delimIt,
                                     ValueParser::parseInteger, ','));
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

            static const std::regex RE_WEEKDAY { "SU|MO|TU|WE|TH|FR|SA" };
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

    RecurrenceRuleOptions opts {
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

} // namespace data
} // namespace ical

