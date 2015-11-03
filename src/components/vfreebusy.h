#ifndef ICAL_COMPONENTS_VFREEBUSY_H
#define ICAL_COMPONENTS_VFREEBUSY_H

#include "core/genericcomponent.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VFreeBusy
{
public:
    VFreeBusy() {}

    void print(std::ostream &out) const;

    static VFreeBusy parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VFREEBUSY_H
