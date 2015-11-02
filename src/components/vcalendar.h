#ifndef ICAL_COMPONENTS_VCALENDAR_H
#define ICAL_COMPONENTS_VCALENDAR_H

#include <ostream>
#include <vector>
#include <string>

#include "core/genericcomponent.h"
#include "parserexception.h"

/* Properties */

/* Components */
#include "components/vevent.h"
#include "components/vjournal.h"
#include "components/vtodo.h"
#include "components/vfreebusy.h"
#include "components/vtimezone.h"

namespace ical {
namespace components {

class VCalendar
{
private:
    /* Components declaration */
    /* At least one MUST be present */
    /* At most 1 of each kind can be present */
    std::vector<ical::components::VEvent> eventComp;
    std::vector<ical::components::VJournal> journalComp;
    std::vector<ical::components::VTodo> todoComp;
    std::vector<ical::components::VFreeBusy> freeBusyComp;
    std::vector<ical::components::VTimeZone> timeZoneComp;

public:
    VCalendar() {}

    void print(std::ostream &out);

    static VCalendar parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VCALENDAR_H
