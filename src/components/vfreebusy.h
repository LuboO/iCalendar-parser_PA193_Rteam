#ifndef ICAL_COMPONENTS_VFREEBUSY_H
#define ICAL_COMPONENTS_VFREEBUSY_H

#include "core/genericcomponent.h"
#include "core/uniqueidregistry.h"

#include <ostream>
#include <vector>

#include "properties/dtstamp.h"
#include "properties/uid.h"
#include "properties/contact.h"
#include "properties/dtstart.h"
#include "properties/dtend.h"
#include "properties/organizer.h"
#include "properties/url.h"
#include "properties/attendee.h"
#include "properties/comment.h"
#include "properties/freebusy.h"

namespace ical {
namespace components {

class VFreeBusy
{
private:
    /** EVENT component properties **/
    /* REQUIRED ONCE */
    std::vector<properties::DTStamp> dtStampProp;
    std::vector<properties::Uid> uidProp;
    /* OPTIONAL max ONCE */
    std::vector<properties::Contact> contactProp;
    std::vector<properties::DTStart> dtStartProp;
    std::vector<properties::DTEnd> dtendProp;
    std::vector<properties::Organizer> organizerProp;
    std::vector<properties::Url> urlProp;
    /* OPTIONAL more than ONCE */
    std::vector<properties::Attendee> attendeeProps;
    std::vector<properties::Comment> commentProps;
    std::vector<properties::Freebusy> freebusyProps;
public:
    static const std::string NAME;

    VFreeBusy() {}

    void print(std::ostream &out) const;

    static VFreeBusy parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &uidRegistry);
    const std::vector<properties::DTStamp> getDtStampProp() const noexcept{return dtStampProp;}
    const std::vector<properties::Uid> getUidProp() const noexcept{return uidProp;}
    const std::vector<properties::Contact> getContactProp() const noexcept{return contactProp;}
    const std::vector<properties::DTStart> getDTStartProp() const noexcept{return dtStartProp;}
    const std::vector<properties::DTEnd> getDTEndProp() const noexcept{return dtendProp;}
    const std::vector<properties::Organizer> getOrganizerProp() const noexcept{return organizerProp;}
    const std::vector<properties::Url> getUrlProp() const noexcept{return urlProp;}
    const std::vector<properties::Attendee> getAttendeeProp() const noexcept{return attendeeProps;}
    const std::vector<properties::Comment> getCommentProp() const noexcept{return commentProps;}
    const std::vector<properties::Freebusy> getFreebusyProp() const noexcept{return freebusyProps;}
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VFREEBUSY_H
