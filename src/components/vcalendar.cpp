#include "components/vcalendar.h"

namespace ical {
namespace components {

const std::string VCalendar::NAME = "VCALENDAR";

void VCalendar::print(std::ostream &out) const
{
    out << "BEGIN:" << NAME << "\r\n";
    for(auto &i : prodIdProp) i.print(out);
    for(auto &i : versionProp) i.print(out);
    for(auto &i : calScaleProp) i.print(out);
    for(auto &i : methodProp) i.print(out);
    for(auto &i : eventComps) i.print(out);
    for(auto &i : journalComps) i.print(out);
    for(auto &i : todoComps) i.print(out);
    for(auto &i : freeBusyComps) i.print(out);
    for(auto &i : timeZoneComps) i.print(out);
    out << "END:" << NAME << "\r\n";
}

VCalendar VCalendar::parse(const core::WithPos<core::GenericComponent> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " object");

    VCalendar calendar;
    core::UniqueIdRegistry uidRegistry;
    core::UniqueIdRegistry tzidRegistry;

    /* Storing properties */
    for(const auto &i : generic->getProperties()) {
        if(i->getName().value() == properties::ProdId::NAME) {
            calendar.prodIdProp.push_back(properties::ProdId::parse(i));
        } else if(i->getName().value() == properties::Version::NAME) {
            calendar.versionProp.push_back(properties::Version::parse(i));
        } else if(i->getName().value() == properties::CalScale::NAME) {
            calendar.calScaleProp.push_back(properties::CalScale::parse(i));
        } else if(i->getName().value() == properties::Method::NAME) {
            calendar.methodProp.push_back(properties::Method::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in " + NAME + " component");
        }
    }

    /** Properties sanity checking **/
    /* PRODID and VERSION must be specified */
    if(calendar.prodIdProp.size() != 1)
        throw ParserException(generic.pos() , "PRODID property must be defined ONCE");
    if(calendar.versionProp.size() != 1)
        throw ParserException(generic.pos() , "VERSION property must be defined ONCE");
    /* CALSCALE and METHOD must be specified AT MOST once */
    if(calendar.calScaleProp.size() > 1)
        throw ParserException(generic.pos() , "CALSCALE property can't occurr multiple times");
    if(calendar.methodProp.size() > 1)
        throw ParserException(generic.pos() , "METHOD property can't occurr multiple times");

    /* Storing components */
    for(const auto &i : generic->getSubcomponents()) {
        if(i->getName().value() == components::VEvent::NAME) {
            calendar.eventComps.push_back(VEvent::parse(i, uidRegistry));
        } else if (i->getName().value() == components::VJournal::NAME) {
            calendar.journalComps.push_back(VJournal::parse(i, uidRegistry));
        } else if (i->getName().value() == components::VTodo::NAME) {
            calendar.todoComps.push_back(VTodo::parse(i, uidRegistry));
        } else if (i->getName().value() == components::VFreeBusy::NAME) {
            calendar.freeBusyComps.push_back(VFreeBusy::parse(i, uidRegistry));
        } else if (i->getName().value() == components::VTimeZone::NAME) {
            calendar.timeZoneComps.push_back(VTimeZone::parse(i, tzidRegistry));
        } else {
            throw ParserException(i.pos() , "invalid component in " + NAME + " component");
        }
    }

    /* At least one component MUST be defined */
    if(calendar.eventComps.empty() &&
            calendar.journalComps.empty() &&
            calendar.todoComps.empty() &&
            calendar.freeBusyComps.empty() &&
            calendar.timeZoneComps.empty())
        throw ParserException(generic.pos() ,  NAME + " object must have"
                                              "at least one component specified");

    if(calendar.methodProp.empty()) {
        for(VEvent &i : calendar.eventComps) {
            if(i.getDtStartProp().empty())
                throw ParserException(generic.pos() ,
                                      "VEVENT component must have DTSTART specified "
                                      "unless METHOD is defined in " + NAME + " object");
        }
    }

    return calendar;
}

} // namespace components
} // namespace ical

