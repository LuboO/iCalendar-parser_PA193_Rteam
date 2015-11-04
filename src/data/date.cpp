#include "date.h"

#include <iomanip>

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

} // namespace data
} // namespace ical

