#include "vfreebusy.h"

namespace ical {
namespace components {

const std::string VFreeBusy::NAME = "VFREEBUSY";

void VFreeBusy::print(std::ostream &out) const {

}

VFreeBusy VFreeBusy::parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &uidRegistry)
{
    return {};
}


} // namespace components
} // namespace ical

