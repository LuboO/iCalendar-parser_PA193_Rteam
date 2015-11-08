#include "vtodo.h"

namespace ical {
namespace components {

void VTodo::print(std::ostream &out) const {
    out << "BEGIN:VTODO\r\n";
    for(auto &i : dtStampProp) i.print(out);
    for(auto &i : uidProp) i.print(out);
    for(auto &i : classProp) i.print(out);
    for(auto &i : completedProp) i.print(out);
    for(auto &i : createdProp) i.print(out);
    for(auto &i : descriptionProp) i.print(out);
    for(auto &i : dtStartProp) i.print(out);
    for(auto &i : geoProp) i.print(out);
    for(auto &i : lastModifiedProp) i.print(out);
    for(auto &i : locationProp) i.print(out);
    for(auto &i : organizerProp) i.print(out);
    for(auto &i : percentCompleteProp) i.print(out);
    for(auto &i : priorityProp) i.print(out);
    for(auto &i : recurrenceIdProp) i.print(out);
    for(auto &i : sequenceProp) i.print(out);
    for(auto &i : statusProp) i.print(out);
    for(auto &i : summaryProp) i.print(out);
    for(auto &i : urlProp) i.print(out);
    for(auto &i : rruleProp) i.print(out);
    for(auto &i : dueProp) i.print(out);
    for(auto &i : durationProp) i.print(out);
    for(auto &i : attachProps) i.print(out);
    for(auto &i : attendeeProps) i.print(out);
    for(auto &i : categoriesProps) i.print(out);
    for(auto &i : commentProps) i.print(out);
    for(auto &i : contactProps) i.print(out);
    for(auto &i : exDateProps) i.print(out);
    for(auto &i : requestStatusProps) i.print(out);
    for(auto &i : relatedToProps) i.print(out);
    for(auto &i : resourcesProps) i.print(out);
    for(auto &i : rDateProps) i.print(out);
    for(auto &i : alarmComps) i.print(out);
    out << "END:VTODO\r\n";
}

VTodo VTodo::parse(const core::WithPos<core::GenericComponent> &generic) {
    if(generic->getName().value() != "VTODO")
        throw ParserException(generic.pos() , "invalid name in VTODO component");

    VTodo todo;

    /* Storing properties */
    for(const auto &i : generic->getProperties()) {
        if(i->getName().value() == "DTSTAMP") {
            todo.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if(i->getName().value() == "UID") {
            todo.uidProp.push_back(properties::Uid::parse(i));
        } else if(i->getName().value() == "CLASS") {
            todo.classProp.push_back(properties::Class::parse(i));
        } else if(i->getName().value() == "COMPLETED") {
            todo.completedProp.push_back(properties::Completed::parse(i));
        } else if(i->getName().value() == "CREATED") {
            todo.createdProp.push_back(properties::Created::parse(i));
        } else if(i->getName().value() == "DESCRIPTION") {
            todo.descriptionProp.push_back(properties::Description::parse(i));
        } else if(i->getName().value() == "DTSTART") {
            todo.dtStartProp.push_back(properties::Dtstart::parse(i));
        } else if(i->getName().value() == "GEO") {
            todo.geoProp.push_back(properties::Geo::parse(i));
        } else if(i->getName().value() == "LAST-MODIFIED") {
            todo.lastModifiedProp.push_back(properties::LastModified::parse(i));
        } else if(i->getName().value() == "LOCATION") {
            todo.locationProp.push_back(properties::Location::parse(i));
        } else if(i->getName().value() == "ORGANIZER") {
            todo.organizerProp.push_back(properties::Organizer::parse(i));
        } else if(i->getName().value() == "PERCENT-COMPLETE") {
            todo.percentCompleteProp.push_back(properties::PercentComplete::parse(i));
        } else if(i->getName().value() == "PRIORITY") {
            todo.priorityProp.push_back(properties::Priority::parse(i));
        } else if(i->getName().value() == "RECURRENCE-ID") {
            todo.recurrenceIdProp.push_back(properties::RecurrenceId::parse(i));
        } else if(i->getName().value() == "SEQUENCE") {
            todo.sequenceProp.push_back(properties::Sequence::parse(i));
        } else if(i->getName().value() == "STATUS") {
            todo.statusProp.push_back(properties::Status::parse(i));
        } else if(i->getName().value() == "SUMMARY") {
            todo.summaryProp.push_back(properties::Summary::parse(i));
        } else if(i->getName().value() == "URL") {
            todo.urlProp.push_back(properties::Url::parse(i));
        } else if(i->getName().value() == "RRULE") {
            todo.rruleProp.push_back(properties::RRule::parse(i));
        } else if(i->getName().value() == "DUE") {
            todo.dueProp.push_back(properties::Due::parse(i));
        } else if(i->getName().value() == "DURATION") {
            todo.durationProp.push_back(properties::DurationProp::parse(i));
        } else if(i->getName().value() == "ATTACH") {
            todo.attachProps.push_back(properties::Attach::parse(i));
        } else if(i->getName().value() == "ATTENDEE") {
            todo.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if(i->getName().value() == "CATEGORIES") {
            todo.categoriesProps.push_back(properties::Categories::parse(i));
        } else if(i->getName().value() == "COMMENT") {
            todo.commentProps.push_back(properties::Comment::parse(i));
        } else if(i->getName().value() == "CONTACT") {
            todo.contactProps.push_back(properties::Contact::parse(i));
        } else if(i->getName().value() == "EXDATE") {
            todo.exDateProps.push_back(properties::ExDate::parse(i));
        } else if(i->getName().value() == "REQUEST-STATUS") {
            todo.requestStatusProps.push_back(properties::RequestStatus::parse(i));
        } else if(i->getName().value() == "RELATED-TO") {
            todo.relatedToProps.push_back(properties::RelatedTo::parse(i));
        } else if(i->getName().value() == "RESOURCES") {
            todo.resourcesProps.push_back(properties::Resources::parse(i));
        } else if(i->getName().value() == "RDATE") {
            todo.rDateProps.push_back(properties::RDate::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in VTODO component");
        }
    }
    /** Properties sanity checking **/
    /* Required properties check */
    if(todo.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , "DTSTAMP is required once in VEVENT component");
    if(todo.uidProp.size() != 1)
        throw ParserException(generic.pos() , "UID is required once in VEVENT component");
    /* OPTIONAL properties max ONCE check */
    if(todo.classProp.size() > 1)
        throw ParserException(generic.pos() , "CLASS property can't occurr multiple times");
    if(todo.completedProp.size() > 1)
        throw ParserException(generic.pos() , "COMPLETED property can't occurr multiple times");
    if(todo.createdProp.size() > 1)
        throw ParserException(generic.pos() , "CREATED property can't occurr multiple times");
    if(todo.descriptionProp.size() > 1)
        throw ParserException(generic.pos() , "DESCRIPTION property can't occurr multiple times");
    if(todo.dtStartProp.size() > 1)
        throw ParserException(generic.pos() , "DTSTART property can't occurr multiple times");
    if(todo.geoProp.size() > 1)
        throw ParserException(generic.pos() , "GEO property can't occurr multiple times");
    if(todo.lastModifiedProp.size() > 1)
        throw ParserException(generic.pos() , "LAST-MODIFIED property can't occurr multiple times");
    if(todo.locationProp.size() > 1)
        throw ParserException(generic.pos() , "LOCATION property can't occurr multiple times");
    if(todo.organizerProp.size() > 1)
        throw ParserException(generic.pos() , "ORGANIZER property can't occurr multiple times");
    if(todo.percentCompleteProp.size() > 1)
        throw ParserException(generic.pos() , "PARCENT-COMPLETE property can't occurr multiple times");
    if(todo.priorityProp.size() > 1)
        throw ParserException(generic.pos() , "PRIORITY property can't occurr multiple times");
    if(todo.recurrenceIdProp.size() > 1)
        throw ParserException(generic.pos() , "RECURRENCE-ID property can't occurr multiple times");
    if(todo.sequenceProp.size() > 1)
        throw ParserException(generic.pos() , "SEQUENCE property can't occurr multiple times");
    if(todo.statusProp.size() > 1)
        throw ParserException(generic.pos() , "STATUS property can't occurr multiple times");
    if(todo.summaryProp.size() > 1)
        throw ParserException(generic.pos() , "SUMMARY property can't occurr multiple times");
    if(todo.urlProp.size() > 1)
        throw ParserException(generic.pos() , "URL property can't occurr multiple times");
    if(todo.rruleProp.size() > 1)
        throw ParserException(generic.pos() , "RRULE property can't occurr multiple times");
    if(todo.dueProp.size() > 1)
        throw ParserException(generic.pos() , "DUE property can't occurr multiple times");
    if(todo.durationProp.size() > 1)
        throw ParserException(generic.pos() , "DURATION property can't occurr multiple times");
    /* Both DURATION and DUE can't be present at the same time */
    if(!todo.dueProp.empty() && !todo.durationProp.empty())
        throw ParserException(generic.pos() , "DUE and DURATION cen't be both present");

    //////////////////////////////////////////
    //////////////// TODO ////////////////////
    //////////////////////////////////////////
    /* remaining checks after implementation of DTStart/DTEnd */
    
    // WHEN STATUS is implemented, uncomment this
    /*if(todo.statusProp.size() == 1) {
        if(todo.statusProp.at(0).getValue() != "NEEDS-ACTION" &&
                todo.statusProp.at(0).getValue() != "COMPLETED" &&
                todo.statusProp.at(0).getValue() != "IN-PROCESS" &&
                todo.statusProp.at(0).getValue() != "CANCELLED")
            throw ParserException(generic.pos() , "inalid value in STATUS property");

    }*/

    /* Storing subcomponents */
    for(const auto &i : generic->getSubcomponents()) {
        if(i->getName().value() == "VALARM") {
            todo.alarmComps.push_back(components::VAlarm::parse(i));
        } else {
            throw ParserException(i.pos() ,
                                  "invalid component in VEVENT component");
        }
    }

    return todo;
}

} // namespace components
} // namespace ical
