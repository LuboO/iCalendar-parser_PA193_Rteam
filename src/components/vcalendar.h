#ifndef ICAL_COMPONENTS_VCALENDAR_H
#define ICAL_COMPONENTS_VCALENDAR_H

#include <ostream>
#include <vector>
#include <string>

#include "core/genericcomponent.h"
#include "parserexception.h"

/* Properties */
#include "properties/prodid.h"
#include "properties/version.h"
#include "properties/calscale.h"
#include "properties/method.h"
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
    /* Properties */
    std::vector<properties::ProdId> prodIdProp;
    std::vector<properties::Version> versionProp;
    std::vector<properties::CalScale> calScaleProp;
    std::vector<properties::Method> methodProp;
    /* Components */
    std::vector<VEvent> eventComps;
    std::vector<VJournal> journalComps;
    std::vector<VTodo> todoComps;
    std::vector<VFreeBusy> freeBusyComps;
    std::vector<VTimeZone> timeZoneComps;
public:
    static const std::string NAME;

    VCalendar() {}

    void print(std::ostream &out) const;

    static VCalendar parse(const core::WithPos<core::GenericComponent> &generic);

    const std::vector<properties::ProdId> getProdIdProp() const noexcept {return prodIdProp;}
    const std::vector<properties::Version> getVersionProp() const noexcept {return versionProp;}
    const std::vector<properties::CalScale> getCalScaleProp() const noexcept {return calScaleProp;}
    const std::vector<properties::Method> getMethodProp() const noexcept {return methodProp;}
    const std::vector<VEvent> getEventComp() const noexcept {return eventComps;}
    const std::vector<VJournal> getJournalComp() const noexcept {return journalComps;}
    const std::vector<VTodo> getTodoComp() const noexcept {return todoComps;}
    const std::vector<VFreeBusy> getFreeBusyComp() const noexcept {return freeBusyComps;}
    const std::vector<VTimeZone> getTimeZoneComp() const noexcept {return timeZoneComps;}
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VCALENDAR_H
