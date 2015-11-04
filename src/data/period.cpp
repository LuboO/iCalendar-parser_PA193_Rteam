#include "period.h"

namespace ical {
namespace data {

void Period::print(std::ostream &out) const
{
    start.print(out);
    out << '/';
    if (explicit_) {
        end.print(out);
    } else {
        duration.print(out);
    }
}

} // namespace data
} // namespace ical

