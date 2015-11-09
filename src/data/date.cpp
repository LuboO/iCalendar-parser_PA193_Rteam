#include "date.h"

#include "parserexception.h"

#include <iomanip>
#include <regex>

namespace ical {
namespace data {

void Date::print(std::ostream &out) const
{
    out << std::setfill('0');
    out << std::setw(4) << year;
    out << std::setw(2) << month;
    out << std::setw(2) << day;

    out << std::setw(0) << std::setfill(' ');
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

static unsigned int getDaysInMonth(unsigned int year, unsigned int month)
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

Date Date::parse(const StreamPos &pos,
                 std::string::const_iterator begin,
                 std::string::const_iterator end)
{
    static const std::regex RE_DATE { "^([0-9]{4})([0-9]{2})([0-9]{2})$" };

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

} // namespace data
} // namespace ical

