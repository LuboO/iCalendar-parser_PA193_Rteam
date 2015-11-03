#include "vtimezone.h"

namespace ical {
namespace components {

void VTimeZone::print(std::ostream &out) const {

}

VTimeZone VTimeZone::parse(const core::WithPos<core::GenericComponent> &generic) {
    return {};
}

} // namespace components
} // namespace ical

