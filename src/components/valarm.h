#ifndef ICAL_COMPONENTS_ALARM_H
#define ICAL_COMPONENTS_ALARM_H

#include "core/genericcomponent.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VAlarm
{
public:
    VAlarm() {}

    void print(std::ostream &out) const;

    static VAlarm parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_ALARM_H
