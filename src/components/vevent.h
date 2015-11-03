#ifndef ICAL_COMPONENTS_VEVENT_H
#define ICAL_COMPONENTS_VEVENT_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

/* Properties */

/* Components */
#include "components/valarm.h"

namespace ical {
namespace components {

class VEvent
{
private:
    /* EVENT component properties */
    /* EVENT component components */
    std::vector<ical::components::VAlarm> alarmComp;

public:
    VEvent() {}

    void print(std::ostream &out) const;

    static VEvent parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VEVENT_H
