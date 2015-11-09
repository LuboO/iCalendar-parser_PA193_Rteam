#ifndef ICAL_COMPONENTS_VFREEBUSY_H
#define ICAL_COMPONENTS_VFREEBUSY_H

#include "core/genericcomponent.h"
#include "core/uniqueidregistry.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VFreeBusy
{
public:
    static const std::string NAME;

    VFreeBusy() {}

    void print(std::ostream &out) const;

    static VFreeBusy parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &uidRegistry);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VFREEBUSY_H
