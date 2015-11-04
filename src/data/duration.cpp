#include "duration.h"

namespace ical {
namespace data {

void Duration::print(std::ostream &out) const
{
    if (negative) {
        out << '-';
    }
    out << 'P';
    if (weeks != 0) {
        out << weeks << 'W';
    } else {
        out << 'T';
        out << days << "DT"
            << hours << 'H'
            << minutes << 'M'
            << seconds << 'S';
    }
}

} // namespace data
} // namespace ical

