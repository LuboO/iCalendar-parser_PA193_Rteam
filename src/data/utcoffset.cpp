#include "utcoffset.h"

#include <iomanip>

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

} // namespace data
} // namespace ical

