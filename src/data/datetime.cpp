#include "datetime.h"

namespace ical {
namespace data {

void DateTime::print(std::ostream &out) const
{
    date.print(out);
    if (timeValid) {
        out << 'T';
        time.print(out);
    }
}

} // namespace data
} // namespace ical

