#include "data/time.h"

#include "parserexception.h"

#include <iomanip>
#include <regex>

namespace ical {
namespace data {

void Time::print(std::ostream &out) const
{
    out << std::setfill('0');
    out << std::setw(2) << hour;
    out << std::setw(2) << minute;
    out << std::setw(2) << second;
    if(!local) {
        out << 'Z';
    }

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

Time Time::parse(const StreamPos &pos,
                 std::string::const_iterator begin,
                 std::string::const_iterator end)
{
    static const std::regex RE_TIME { "^([0-9]{2})([0-9]{2})([0-9]{2})(Z?)$" };

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

} // namespace data
} // namespace ical

