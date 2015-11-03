#include "vcalendar.h"

namespace ical {
namespace components {

using namespace ical::core;

void VCalendar::print(std::ostream &out) const
{
    // TODO
}

VCalendar VCalendar::parse(const WithPos<GenericComponent> &generic)
{
    VCalendar calendar;

    const std::vector<WithPos<GenericComponent>> & comps =
            generic->getSubcomponents();

    for(const WithPos<GenericComponent> & i : comps) {
        if(i->getName().value() == "VEVENT") {
            if(calendar.eventComp.size() > 0)
                throw ical::ParserException(
                        i.pos() , "multiple VEVENT components not allowed");
            VEvent event = VEvent::parse(i);
            calendar.eventComp.push_back(event);
        } else if (i->getName().value() == "VJOURNAL") {
            if(calendar.journalComp.size() > 0)
                throw ical::ParserException(
                        i.pos() , "multiple VJOURNAL components not allowed");
            VJournal journal = VJournal::parse(i);
            calendar.journalComp.push_back(journal);
        } else if (i->getName().value() == "VTODO") {
            if(calendar.todoComp.size() > 0)
                throw ical::ParserException(
                        i.pos() , "multiple VTODO components not allowed");
            VTodo todo = VTodo::parse(i);
            calendar.todoComp.push_back(todo);
        } else if (i->getName().value() == "VFREEBUSY") {
            if(calendar.freeBusyComp.size() > 0)
                throw ical::ParserException(
                        i.pos() , "multiple VFREEBUSY components not allowed");
            VFreeBusy freeBusy = VFreeBusy::parse(i);
            calendar.freeBusyComp.push_back(freeBusy);
        } else if (i->getName().value() == "VTIMEZONE") {
            if(calendar.timeZoneComp.size() > 0)
                throw ical::ParserException(
                        i.pos() , "multiple VTIMEZONE components not allowed");
            VTimeZone timeZone = VTimeZone::parse(i);
            calendar.timeZoneComp.push_back(timeZone);
        } else {
            throw ical::ParserException(i.pos() , "unknown component");
        }
    }
    return calendar;
}

} // namespace components
} // namespace ical

