#ifndef ICAL_COMPONENTS_VTIMEZONE_H
#define ICAL_COMPONENTS_VTIMEZONE_H

#include "core/genericcomponent.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VTimeZone
{
public:
    VTimeZone() {}

    void print(std::ostream &out) const;

    static VTimeZone parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VTIMEZONE_H
