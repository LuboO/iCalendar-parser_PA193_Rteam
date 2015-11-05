#ifndef ICAL_COMPONENTS_VEVENT_H
#define ICAL_COMPONENTS_VEVENT_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

/** Properties **/
#include "properties/dtstamp.h"
#include "properties/uid.h"
#include "properties/dtstart.h"
#include "properties/class.h"
#include "properties/created.h"
#include "properties/description.h"
#include "properties/geo.h"
#include "properties/lastmodified.h"
#include "properties/location.h"
#include "properties/organizer.h"
#include "properties/priority.h"
#include "properties/sequence.h"
#include "properties/status.h"
#include "properties/summary.h"
#include "properties/transp.h"
#include "properties/url.h"
#include "properties/recurrenceid.h"
#include "properties/rrule.h"
#include "properties/dtend.h"
#include "properties/durationprop.h"
#include "properties/attach.h"
#include "properties/attendee.h"
#include "properties/categories.h"
#include "properties/comment.h"
#include "properties/contact.h"
#include "properties/exdate.h"
#include "properties/requeststatus.h"
#include "properties/relatedto.h"
#include "properties/resources.h"
#include "properties/rdate.h"

/** Components **/
#include "components/valarm.h"

namespace ical {
namespace components {

class VEvent
{
private:
    /** EVENT component properties **/
    /* REQUIRED ONCE */
    std::vector<properties::DTStamp> dtStampProp;
    std::vector<properties::Uid> uidProp;
    /* REQUIRED ONCE if METHOD is specified */
    /* Otherwise OPTIONAL ONCE */
    std::vector<properties::Dtstart> dtStartProp;
    /* OPTIONAL max ONCE */
    std::vector<properties::Class> classProp;
    std::vector<properties::Created> createdProp;
    std::vector<properties::Description> descriptionProp;
    std::vector<properties::Geo> geoProp;
    std::vector<properties::LastModified> lastModifiedProp;
    std::vector<properties::Location> locationProp;
    std::vector<properties::Organizer> organizerProp;
    std::vector<properties::Priority> priorityProp;
    std::vector<properties::Sequence> sequenceProp;
    std::vector<properties::Status> statusProp;
    std::vector<properties::Summary> summaryProp;
    std::vector<properties::Transp> transpProp;
    std::vector<properties::Url> urlProp;
    std::vector<properties::RecurrenceId> recurrenceIdProp;
    std::vector<properties::RRule> rruleProp;
    /* OPTIONAL max ONCE but both can't be set */
    std::vector<properties::DTEND> dtEndProp;
    std::vector<properties::DurationProp> durationProp;
    /* OPTIONAL more than ONCE */
    std::vector<properties::Attach> attachProps;
    std::vector<properties::Attendee> attendeeProps;
    std::vector<properties::Categories> categoriesProps;
    std::vector<properties::Comment> commentProps;
    std::vector<properties::Contact> contactProps;
    std::vector<properties::ExDate> exDateProps;
    std::vector<properties::RequestStatus> requestStatusProps;
    std::vector<properties::RelatedTo> relatedToProps;
    std::vector<properties::Resources> resourcesProps;
    std::vector<properties::RDate> rDateProps;

    /** EVENT component components **/
    /* OPTIONAL more than ONCE */
    std::vector<components::VAlarm> alarmComps;
public:
    VEvent() {}

    void print(std::ostream &out) const;

    static VEvent parse(const core::WithPos<core::GenericComponent> &generic);

    /* GETTERS FOR EVERYONE!!! */
    const std::vector<properties::DTStamp> &getDtStampProp() const noexcept{return dtStampProp;}
    const std::vector<properties::Uid> &getUidProp() const noexcept{return uidProp;}
    const std::vector<properties::Dtstart> &getDtStartProp() const noexcept{return dtStartProp;}
    const std::vector<properties::Class> &getClassProp() const noexcept{return classProp;}
    const std::vector<properties::Created> &getCreatedProp() const noexcept{return createdProp;}
    const std::vector<properties::Description> &getDescriptionProp() const noexcept{return descriptionProp;}
    const std::vector<properties::Geo> &getGeoProp() const noexcept{return geoProp;}
    const std::vector<properties::LastModified> &getLastModifiedProp() const noexcept{return lastModifiedProp;}
    const std::vector<properties::Location> &getLocationProp() const noexcept{return locationProp;}
    const std::vector<properties::Organizer> &getOrganizerProp() const noexcept{return organizerProp;}
    const std::vector<properties::Priority> &getPriorityProp() const noexcept{return priorityProp;}
    const std::vector<properties::Sequence> &getSequenceProp() const noexcept{return sequenceProp;}
    const std::vector<properties::Status> &getStatusProp() const noexcept{return statusProp;}
    const std::vector<properties::Summary> &getSummaryProp() const noexcept{return summaryProp;}
    const std::vector<properties::Transp> &getTranspProp() const noexcept{return transpProp;}
    const std::vector<properties::Url> &getUrlProp() const noexcept{return urlProp;}
    const std::vector<properties::RecurrenceId> &getRecurrenceIdProp() const noexcept{ return recurrenceIdProp;}
    const std::vector<properties::RRule> &getRruleProp() const noexcept{return rruleProp;}
    const std::vector<properties::DTEND> &getDtEndProp() const noexcept{return dtEndProp;}
    const std::vector<properties::DurationProp> &getDurationProp() const noexcept{return durationProp;}
    const std::vector<properties::Attach> &getAttachProps() const noexcept{return attachProps;}
    const std::vector<properties::Attendee> &getAttendeeProps() const noexcept{return attendeeProps;}
    const std::vector<properties::Categories> &getCategoriesProps() const noexcept{return categoriesProps;}
    const std::vector<properties::Comment> &getCommentProps() const noexcept{return commentProps;}
    const std::vector<properties::Contact> &getContactProps() const noexcept{return contactProps;}
    const std::vector<properties::ExDate> &getExDateProps() const noexcept{return exDateProps;}
    const std::vector<properties::RequestStatus> &getRequestStatusProps() const noexcept{return requestStatusProps;}
    const std::vector<properties::RelatedTo> &getRelatedToProps() const noexcept{return relatedToProps;}
    const std::vector<properties::Resources> &getResourcesProps() const noexcept{return resourcesProps;}
    const std::vector<properties::RDate> &getRDateProps() const noexcept{return rDateProps;}
    const std::vector<components::VAlarm> &getAlarmComps() const noexcept{return alarmComps;}
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VEVENT_H
