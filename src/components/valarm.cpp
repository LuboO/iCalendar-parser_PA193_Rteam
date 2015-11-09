#include "valarm.h"

namespace ical {
namespace components {

const std::string VAlarm::NAME = "VALARM";

void VAlarm::print(std::ostream &out) const {

}

VAlarm VAlarm::parse(const core::WithPos<core::GenericComponent> &generic) {
    return {};
}

} // namespace components
} // namespace ical

