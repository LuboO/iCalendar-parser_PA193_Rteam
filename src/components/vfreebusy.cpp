#include "vfreebusy.h"

namespace ical {
namespace components {

void VFreeBusy::print(std::ostream &out) const {

}

VFreeBusy VFreeBusy::parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &uidRegistry)
{
    return {};
}


} // namespace components
} // namespace ical

