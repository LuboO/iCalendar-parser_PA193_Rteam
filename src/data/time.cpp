#include "time.h"

#include <iomanip>

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

} // namespace data
} // namespace ical

