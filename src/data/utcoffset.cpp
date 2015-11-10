#include "data/utcoffset.h"

#include "parserexception.h"

#include <iomanip>
#include <regex>

namespace ical {
namespace data {

void UTCOffset::print(std::ostream &out) const
{
    if (negative) {
        out << '-';
    } else {
        out << '+';
    }
    out << std::setfill('0');
    out << std::setw(2) << hours;
    out << std::setw(2) << minutes;
    out << std::setw(2) << seconds;

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

UTCOffset UTCOffset::parse(const StreamPos &pos,
                           std::string::const_iterator begin,
                           std::string::const_iterator end)
{
    static const std::regex RE_UTC_OFFSET { "([+-])([0-9]{2})([0-9]{2})([0-9]{2})?" };
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

} // namespace data
} // namespace ical

