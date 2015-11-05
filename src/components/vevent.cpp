#include "vevent.h"

namespace ical {
namespace components {

void VEvent::print(std::ostream &out) const {
    //todo
}

VEvent VEvent::parse(const core::WithPos<core::GenericComponent> &generic) {
    if(generic->getName().value() != "VEVENT")
        throw ParserException(generic.pos() , "invalid name in VEVENT component");

    VEvent event;

    /* Storing properties */
    for(const auto &i : generic->getProperties()) {
        if(i->getName().value() == "DTSTAMP") {
            event.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if (i->getName().value() == "UID") {
            event.uidProp.push_back(properties::Uid::parse(i));
        } else if (i->getName().value() == "DTSTART") {
            event.dtStartProp.push_back(properties::Dtstart::parse(i));
        } else if (i->getName().value() == "CLASS") {
            event.classProp.push_back(properties::Class::parse(i));
        } else if (i->getName().value() == "CREATED") {
            event.createdProp.push_back(properties::Created::parse(i));
        } else if (i->getName().value() == "DESCRIPTION") {
            event.descriptionProp.push_back(properties::Description::parse(i));
        } else if (i->getName().value() == "GEO") {
            event.geoProp.push_back(properties::Geo::parse(i));
        } else if (i->getName().value() == "LAST-MODIFIED") {
            event.lastModifiedProp.push_back(properties::LastModified::parse(i));
        } else if (i->getName().value() == "LOCATION") {
            event.locationProp.push_back(properties::Location::parse(i));
        } else if (i->getName().value() == "ORGANIZER") {
            event.organizerProp.push_back(properties::Organizer::parse(i));
        } else if (i->getName().value() == "PRIORITY") {
            event.priorityProp.push_back(properties::Priority::parse(i));
        } else if (i->getName().value() == "SEQUENCE") {
            event.sequenceProp.push_back(properties::Sequence::parse(i));
        } else if (i->getName().value() == "STATUS") {
            event.statusProp.push_back(properties::Status::parse(i));
        } else if (i->getName().value() == "SUMMARY") {
            event.summaryProp.push_back(properties::Summary::parse(i));
        } else if (i->getName().value() == "TRANSP") {
            event.transpProp.push_back(properties::Transp::parse(i));
        } else if (i->getName().value() == "URL") {
            event.urlProp.push_back(properties::Url::parse(i));
        } else if (i->getName().value() == "RECURRENCE-ID") {
            event.recurrenceIdProp.push_back(properties::RecurrenceId::parse(i));
        } else if (i->getName().value() == "RRULE") {
            event.rruleProp.push_back(properties::RRule::parse(i));
        } else if (i->getName().value() == "DTEND") {
            event.dtEndProp.push_back(properties::DTEND::parse(i));
        } else if (i->getName().value() == "DURATION") {
            event.durationProp.push_back(properties::DurationProp::parse(i));
        } else if (i->getName().value() == "ATTACH") {
            event.attachProps.push_back(properties::Attach::parse(i));
        } else if (i->getName().value() == "ATTENDEE") {
            event.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if (i->getName().value() == "CATEGORIES") {
            event.categoriesProps.push_back(properties::Categories::parse(i));
        } else if (i->getName().value() == "COMMENT") {
            event.commentProps.push_back(properties::Comment::parse(i));
        } else if (i->getName().value() == "CONTACT") {
            event.contactProps.push_back(properties::Contact::parse(i));
        } else if (i->getName().value() == "EXDATE") {
            event.exDateProps.push_back(properties::ExDate::parse(i));
        } else if (i->getName().value() == "REQUEST-STATUS") {
            event.requestStatusProps.push_back(properties::RequestStatus::parse(i));
        } else if (i->getName().value() == "RELATED-TO") {
            event.relatedToProps.push_back(properties::RelatedTo::parse(i));
        } else if (i->getName().value() == "RESOURCES") {
            event.resourcesProps.push_back(properties::Resources::parse(i));
        } else if (i->getName().value() == "RDATE") {
            event.rDateProps.push_back(properties::RDate::parse(i));
        } else {
            throw ParserException(i.pos() ,
                                  "invalid property in VEVENT component");
        }
    }
    /** Properties sanity checking **/
    /* Required properties check */
    if(event.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , "DTSTAMP is required once in VEVENT component");
    if(event.uidProp.size() != 1)
        throw ParserException(generic.pos() , "UID is required once in VEVENT component");
    /* OPTIONAL properties max ONCE check */
    if(event.classProp.size() > 1)
        throw ParserException(generic.pos() , "CLASS property can't occurr multiple times");
    if(event.createdProp.size() > 1)
        throw ParserException(generic.pos() , "CREATED property can't occurr multiple times");
    if(event.descriptionProp.size() > 1)
        throw ParserException(generic.pos() , "DESCRIPTION property can't occurr multiple times");
    if(event.geoProp.size() > 1)
        throw ParserException(generic.pos() , "GEO property can't occurr multiple times");
    if(event.lastModifiedProp.size() > 1)
        throw ParserException(generic.pos() , "LAST-MODIFIED property can't occurr multiple times");
    if(event.locationProp.size() > 1)
        throw ParserException(generic.pos() , "LOCATION property can't occurr multiple times");
    if(event.organizerProp.size() > 1)
        throw ParserException(generic.pos() , "ORGANIZER property can't occurr multiple times");
    if(event.priorityProp.size() > 1)
        throw ParserException(generic.pos() , "PRIORITY property can't occurr multiple times");
    if(event.sequenceProp.size() > 1)
        throw ParserException(generic.pos() , "SEQUENCE property can't occurr multiple times");
    if(event.statusProp.size() > 1)
        throw ParserException(generic.pos() , "STATUS property can't occurr multiple times");
    if(event.summaryProp.size() > 1)
        throw ParserException(generic.pos() , "SUMMARY property can't occurr multiple times");
    if(event.transpProp.size() > 1)
        throw ParserException(generic.pos() , "TRANSP property can't occurr multiple times");
    if(event.urlProp.size() > 1)
        throw ParserException(generic.pos() , "URL property can't occurr multiple times");
    if(event.recurrenceIdProp.size() > 1)
        throw ParserException(generic.pos() , "RECURRENCE-ID property can't occurr multiple times");
    if(event.rruleProp.size() > 1)
        throw ParserException(generic.pos() , "RRULE property can't occurr multiple times");
    if(event.dtEndProp.size() > 1)
        throw ParserException(generic.pos() , "DTEND property can't occurr multiple times");
    if(event.durationProp.size() > 1)
        throw ParserException(generic.pos() , "DURATION property can't occurr multiple times");
    /* Both DTEND and DURATION can't be present at the same time */
    if(!event.dtEndProp.empty() && !event.durationProp.empty())
        throw ParserException(generic.pos() , "DTEND and DURATION can't be both present");


    //////////////////////////////////////////
    //////////////// TODO ////////////////////
    //////////////////////////////////////////
    /* remaining checks after implementation of DTStart/DTEnd */

    /* Storing subcomponents */
    for(const auto &i : generic->getSubcomponents()) {
        if(i->getName().value() == "VALARM") {
            event.alarmComps.push_back(components::VAlarm::parse(i));

        } else {
            throw ParserException(i.pos() ,
                                  "invalid component in VEVENT component");
        }
    }

    return event;
}

} // namespace components
} // namespace ical

