#include "vcalendar.h"

namespace ical {
namespace components {

void VCalendar::print(std::ostream &out) const
{
    out << "BEGIN:VCALENDAR\r\n";
    for(auto &i : prodIdProp) i.print(out);
    for(auto &i : versionProp) i.print(out);
    for(auto &i : calScaleProp) i.print(out);
    for(auto &i : methodProp) i.print(out);
    for(auto &i : eventComps) i.print(out);
    for(auto &i : journalComps) i.print(out);
    for(auto &i : todoComps) i.print(out);
    for(auto &i : freeBusyComps) i.print(out);
    for(auto &i : timeZoneComps) i.print(out);
    out << "END:VCALENDAR\r\n";
}

VCalendar VCalendar::parse(const core::WithPos<core::GenericComponent> &generic) {
    if(generic->getName().value() != "VCALENDAR")
        throw ParserException(generic.pos() , "invalid name in VCALENDAR object");

    VCalendar calendar;
    core::UniqueIdRegistry uidRegistry;
    core::UniqueIdRegistry tzidRegistry;

    /* Storing properties */
    for(const auto &i : generic->getProperties()) {
        if(i->getName().value() == "PRODID") {
            calendar.prodIdProp.push_back(properties::ProdId::parse(i));
        } else if(i->getName().value() == "VERSION") {
            calendar.versionProp.push_back(properties::Version::parse(i));
        } else if(i->getName().value() == "CALSCALE") {
            calendar.calScaleProp.push_back(properties::CalScale::parse(i));
        } else if(i->getName().value() == "METHOD") {
            calendar.methodProp.push_back(properties::Method::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in VCALENDAR component");
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
        if(i->getName().value() == "VEVENT") {
            calendar.eventComps.push_back(VEvent::parse(i, uidRegistry));
        } else if (i->getName().value() == "VJOURNAL") {
            calendar.journalComps.push_back(VJournal::parse(i, uidRegistry));
        } else if (i->getName().value() == "VTODO") {
            calendar.todoComps.push_back(VTodo::parse(i, uidRegistry));
        } else if (i->getName().value() == "VFREEBUSY") {
            calendar.freeBusyComps.push_back(VFreeBusy::parse(i, uidRegistry));
        } else if (i->getName().value() == "VTIMEZONE") {
            calendar.timeZoneComps.push_back(VTimeZone::parse(i, tzidRegistry));
        } else {
            throw ParserException(i.pos() , "invalid component in VCALENDAR component");
        }
    }

    /* At least one component MUST be defined */
    if(calendar.eventComps.empty() &&
            calendar.journalComps.empty() &&
            calendar.todoComps.empty() &&
            calendar.freeBusyComps.empty() &&
            calendar.timeZoneComps.empty())
        throw ParserException(generic.pos() , "VCALENDAR object must have"
                                              "at least one component specified");

    /** VEVENT checks **/
    /*if(calendar.methodProp.empty() &&
            calendar.eventComps.size() == 1 &&
            calendar.eventComps.at(0).getDtStartProp().empty())
        throw ParserException(generic.pos() ,
                              "when METHOD is not specified, VEVENT component "
                              "must have DTSTART specified");*/
    if(calendar.methodProp.empty()) {
        for(VEvent &i : calendar.eventComps) {
            if(i.getDtStartProp().empty())
                throw ParserException(generic.pos() ,
                                      "VEVENT component must have DTSTART specified "
                                      "unless METHOD is defined in VCALENDAR object");
        }
    }

    return calendar;
}

} // namespace components
} // namespace ical

