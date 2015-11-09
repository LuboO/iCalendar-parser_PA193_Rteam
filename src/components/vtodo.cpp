#include "vtodo.h"

namespace ical {
namespace components {

const std::string VTodo::NAME = "VTODO";

void VTodo::print(std::ostream &out) const {
    out << "BEGIN:" << NAME << "\r\n";
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
    out << "END:" << NAME << "\r\n";
}

VTodo VTodo::parse(const core::WithPos<core::GenericComponent> &generic,
                   core::UniqueIdRegistry &uidRegistry)
{
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " component");

    VTodo todo;

    /* Storing properties */
    for(const auto &i : generic->getProperties()) {
        if(i->getName().value() == properties::DTStamp::NAME) {
            todo.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if(i->getName().value() == properties::Uid::NAME) {
            todo.uidProp.push_back(properties::Uid::parse(i));
        } else if(i->getName().value() == properties::Class::NAME) {
            todo.classProp.push_back(properties::Class::parse(i));
        } else if(i->getName().value() == properties::Completed::NAME) {
            todo.completedProp.push_back(properties::Completed::parse(i));
        } else if(i->getName().value() == properties::Created::NAME) {
            todo.createdProp.push_back(properties::Created::parse(i));
        } else if(i->getName().value() == properties::Description::NAME) {
            todo.descriptionProp.push_back(properties::Description::parse(i));
        } else if(i->getName().value() == properties::DTStart::NAME) {
            todo.dtStartProp.push_back(properties::DTStart::parse(i));
        } else if(i->getName().value() == properties::Geo::NAME) {
            todo.geoProp.push_back(properties::Geo::parse(i));
        } else if(i->getName().value() == properties::LastModified::NAME) {
            todo.lastModifiedProp.push_back(properties::LastModified::parse(i));
        } else if(i->getName().value() == properties::Location::NAME) {
            todo.locationProp.push_back(properties::Location::parse(i));
        } else if(i->getName().value() == properties::Organizer::NAME) {
            todo.organizerProp.push_back(properties::Organizer::parse(i));
        } else if(i->getName().value() == properties::PercentComplete::NAME) {
            todo.percentCompleteProp.push_back(properties::PercentComplete::parse(i));
        } else if(i->getName().value() == properties::Priority::NAME) {
            todo.priorityProp.push_back(properties::Priority::parse(i));
        } else if(i->getName().value() == properties::RecurrenceId::NAME) {
            todo.recurrenceIdProp.push_back(properties::RecurrenceId::parse(i));
        } else if(i->getName().value() == properties::Sequence::NAME) {
            todo.sequenceProp.push_back(properties::Sequence::parse(i));
        } else if(i->getName().value() == properties::Status::NAME) {
            todo.statusProp.push_back(properties::Status::parse(i));
        } else if(i->getName().value() == properties::Summary::NAME) {
            todo.summaryProp.push_back(properties::Summary::parse(i));
        } else if(i->getName().value() == properties::Url::NAME) {
            todo.urlProp.push_back(properties::Url::parse(i));
        } else if(i->getName().value() == properties::RRule::NAME) {
            todo.rruleProp.push_back(properties::RRule::parse(i));
        } else if(i->getName().value() == properties::Due::NAME) {
            todo.dueProp.push_back(properties::Due::parse(i));
        } else if(i->getName().value() == properties::DurationProp::NAME) {
            todo.durationProp.push_back(properties::DurationProp::parse(i));
        } else if(i->getName().value() == properties::Attach::NAME) {
            todo.attachProps.push_back(properties::Attach::parse(i));
        } else if(i->getName().value() == properties::Attendee::NAME) {
            todo.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if(i->getName().value() == properties::Categories::NAME) {
            todo.categoriesProps.push_back(properties::Categories::parse(i));
        } else if(i->getName().value() == properties::Comment::NAME) {
            todo.commentProps.push_back(properties::Comment::parse(i));
        } else if(i->getName().value() == properties::Contact::NAME) {
            todo.contactProps.push_back(properties::Contact::parse(i));
        } else if(i->getName().value() == properties::ExDate::NAME) {
            todo.exDateProps.push_back(properties::ExDate::parse(i));
        } else if(i->getName().value() == properties::RequestStatus::NAME) {
            todo.requestStatusProps.push_back(properties::RequestStatus::parse(i));
        } else if(i->getName().value() == properties::RelatedTo::NAME) {
            todo.relatedToProps.push_back(properties::RelatedTo::parse(i));
        } else if(i->getName().value() == properties::Resources::NAME) {
            todo.resourcesProps.push_back(properties::Resources::parse(i));
        } else if(i->getName().value() == properties::RDate::NAME) {
            todo.rDateProps.push_back(properties::RDate::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in " + NAME + " component");
        }
    }
    /** Properties sanity checking **/
    /* Required properties check */
    if(todo.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , properties::DTStamp::NAME + " is required once in " + NAME + " component");
    if(todo.uidProp.size() != 1)
        throw ParserException(generic.pos() , properties::Uid::NAME + " is required once in " + NAME + " component");
    /* OPTIONAL properties max ONCE check */
    if(todo.classProp.size() > 1)
        throw ParserException(generic.pos() , properties::Class::NAME + " property can't occurr multiple times");
    if(todo.completedProp.size() > 1)
        throw ParserException(generic.pos() , properties::Completed::NAME + " property can't occurr multiple times");
    if(todo.createdProp.size() > 1)
        throw ParserException(generic.pos() , properties::Created::NAME + " property can't occurr multiple times");
    if(todo.descriptionProp.size() > 1)
        throw ParserException(generic.pos() , properties::Description::NAME + " property can't occurr multiple times");
    if(todo.dtStartProp.size() > 1)
        throw ParserException(generic.pos() , properties::DTStart::NAME + " property can't occurr multiple times");
    if(todo.geoProp.size() > 1)
        throw ParserException(generic.pos() , properties::Geo::NAME + " property can't occurr multiple times");
    if(todo.lastModifiedProp.size() > 1)
        throw ParserException(generic.pos() , properties::LastModified::NAME + " property can't occurr multiple times");
    if(todo.locationProp.size() > 1)
        throw ParserException(generic.pos() , properties::Location::NAME + " property can't occurr multiple times");
    if(todo.organizerProp.size() > 1)
        throw ParserException(generic.pos() , properties::Organizer::NAME + " property can't occurr multiple times");
    if(todo.percentCompleteProp.size() > 1)
        throw ParserException(generic.pos() , properties::PercentComplete::NAME + " property can't occurr multiple times");
    if(todo.priorityProp.size() > 1)
        throw ParserException(generic.pos() , properties::Priority::NAME + " property can't occurr multiple times");
    if(todo.recurrenceIdProp.size() > 1)
        throw ParserException(generic.pos() , properties::RecurrenceId::NAME + " property can't occurr multiple times");
    if(todo.sequenceProp.size() > 1)
        throw ParserException(generic.pos() , properties::Sequence::NAME + " property can't occurr multiple times");
    if(todo.statusProp.size() > 1)
        throw ParserException(generic.pos() , properties::Status::NAME + " property can't occurr multiple times");
    if(todo.summaryProp.size() > 1)
        throw ParserException(generic.pos() , properties::Summary::NAME + " property can't occurr multiple times");
    if(todo.urlProp.size() > 1)
        throw ParserException(generic.pos() , properties::Url::NAME + " property can't occurr multiple times");
    if(todo.rruleProp.size() > 1)
        throw ParserException(generic.pos() , properties::RRule::NAME + " property can't occurr multiple times");
    if(todo.dueProp.size() > 1)
        throw ParserException(generic.pos() , properties::Due::NAME + " property can't occurr multiple times");
    if(todo.durationProp.size() > 1)
        throw ParserException(generic.pos() , properties::DurationProp::NAME + " property can't occurr multiple times");
    /* Both DURATION and DUE can't be present at the same time */
    if(!todo.dueProp.empty() && !todo.durationProp.empty())
        throw ParserException(generic.pos() , properties::Due::NAME + " and " +
                              properties::DurationProp::NAME + " can't be both present");

    if (!uidRegistry.registerId(todo.uidProp[0].getValue())) {
        throw ParserException(generic.pos() , "The value of the " +properties::Uid::NAME + " property must be globally unique");
    }

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
        if(i->getName().value() == components::VAlarm::NAME) {
            todo.alarmComps.push_back(components::VAlarm::parse(i));
        } else {
            throw ParserException(i.pos() ,
                                  "invalid component in " + NAME + " component");
        }
    }

    return todo;
}

} // namespace components
} // namespace ical
