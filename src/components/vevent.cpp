#include "components/vevent.h"

namespace ical {
namespace components {

const std::string VEvent::NAME = "VEVENT";

void VEvent::print(std::ostream &out) const {
    out << "BEGIN:" << NAME << "\r\n";
    for(auto &i : dtStampProp) i.print(out);
    for(auto &i : uidProp) i.print(out);
    for(auto &i : dtStartProp) i.print(out);
    for(auto &i : classProp) i.print(out);
    for(auto &i : createdProp) i.print(out);
    for(auto &i : descriptionProp) i.print(out);
    for(auto &i : geoProp) i.print(out);
    for(auto &i : lastModifiedProp) i.print(out);
    for(auto &i : locationProp) i.print(out);
    for(auto &i : organizerProp) i.print(out);
    for(auto &i : priorityProp) i.print(out);
    for(auto &i : sequenceProp) i.print(out);
    for(auto &i : statusProp) i.print(out);
    for(auto &i : summaryProp) i.print(out);
    for(auto &i : transpProp) i.print(out);
    for(auto &i : urlProp) i.print(out);
    for(auto &i : recurrenceIdProp) i.print(out);
    for(auto &i : rruleProp) i.print(out);
    for(auto &i : dtEndProp) i.print(out);
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

VEvent VEvent::parse(const core::WithPos<core::GenericComponent> &generic,
                     core::UniqueIdRegistry &uidRegistry)
{
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " component");

    VEvent event;

    /* Storing properties */
    for(const auto &i : generic->getProperties()) {
        if(i->getName().value() == properties::DTStamp::NAME) {
            event.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if (i->getName().value() == properties::Uid::NAME) {
            event.uidProp.push_back(properties::Uid::parse(i));
        } else if (i->getName().value() == properties::DTStart::NAME) {
            event.dtStartProp.push_back(properties::DTStart::parse(i));
        } else if (i->getName().value() == properties::Class::NAME) {
            event.classProp.push_back(properties::Class::parse(i));
        } else if (i->getName().value() == properties::Created::NAME) {
            event.createdProp.push_back(properties::Created::parse(i));
        } else if (i->getName().value() == properties::Description::NAME) {
            event.descriptionProp.push_back(properties::Description::parse(i));
        } else if (i->getName().value() == properties::Geo::NAME) {
            event.geoProp.push_back(properties::Geo::parse(i));
        } else if (i->getName().value() == properties::LastModified::NAME) {
            event.lastModifiedProp.push_back(properties::LastModified::parse(i));
        } else if (i->getName().value() == properties::Location::NAME) {
            event.locationProp.push_back(properties::Location::parse(i));
        } else if (i->getName().value() == properties::Organizer::NAME) {
            event.organizerProp.push_back(properties::Organizer::parse(i));
        } else if (i->getName().value() == properties::Priority::NAME) {
            event.priorityProp.push_back(properties::Priority::parse(i));
        } else if (i->getName().value() == properties::Sequence::NAME) {
            event.sequenceProp.push_back(properties::Sequence::parse(i));
        } else if (i->getName().value() == properties::Status::NAME) {
            event.statusProp.push_back(properties::Status::parse(i));
        } else if (i->getName().value() == properties::Summary::NAME) {
            event.summaryProp.push_back(properties::Summary::parse(i));
        } else if (i->getName().value() == properties::Transp::NAME) {
            event.transpProp.push_back(properties::Transp::parse(i));
        } else if (i->getName().value() == properties::Url::NAME) {
            event.urlProp.push_back(properties::Url::parse(i));
        } else if (i->getName().value() == properties::RecurrenceId::NAME) {
            event.recurrenceIdProp.push_back(properties::RecurrenceId::parse(i));
        } else if (i->getName().value() == properties::RRule::NAME) {
            event.rruleProp.push_back(properties::RRule::parse(i));
        } else if (i->getName().value() == properties::DTEnd::NAME) {
            event.dtEndProp.push_back(properties::DTEnd::parse(i));
        } else if (i->getName().value() == properties::DurationProp::NAME) {
            event.durationProp.push_back(properties::DurationProp::parse(i));
        } else if (i->getName().value() == properties::Attach::NAME) {
            event.attachProps.push_back(properties::Attach::parse(i));
        } else if (i->getName().value() == properties::Attendee::NAME) {
            event.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if (i->getName().value() == properties::Categories::NAME) {
            event.categoriesProps.push_back(properties::Categories::parse(i));
        } else if (i->getName().value() == properties::Comment::NAME) {
            event.commentProps.push_back(properties::Comment::parse(i));
        } else if (i->getName().value() == properties::Contact::NAME) {
            event.contactProps.push_back(properties::Contact::parse(i));
        } else if (i->getName().value() == properties::ExDate::NAME) {
            event.exDateProps.push_back(properties::ExDate::parse(i));
        } else if (i->getName().value() == properties::RequestStatus::NAME) {
            event.requestStatusProps.push_back(properties::RequestStatus::parse(i));
        } else if (i->getName().value() == properties::RelatedTo::NAME) {
            event.relatedToProps.push_back(properties::RelatedTo::parse(i));
        } else if (i->getName().value() == properties::Resources::NAME) {
            event.resourcesProps.push_back(properties::Resources::parse(i));
        } else if (i->getName().value() == properties::RDate::NAME) {
            event.rDateProps.push_back(properties::RDate::parse(i));
        } else {
            throw ParserException(i.pos() ,
                                  "invalid property in " + NAME + " component");
        }
    }
    /** Properties sanity checking **/
    /* Required properties check */
    if(event.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , properties::DTStamp::NAME + " is required once in " + NAME + " component");
    if(event.uidProp.size() != 1)
        throw ParserException(generic.pos() , properties::Uid::NAME + " is required once in " + NAME + " component");
    /* OPTIONAL properties max ONCE check */
    if(event.dtStartProp.size() > 1)
        throw ParserException(generic.pos() , properties::DTStart::NAME + " property can't occurr multiple times");
    if(event.classProp.size() > 1)
        throw ParserException(generic.pos() , properties::Class::NAME + " property can't occurr multiple times");
    if(event.createdProp.size() > 1)
        throw ParserException(generic.pos() , properties::Created::NAME + " property can't occurr multiple times");
    if(event.descriptionProp.size() > 1)
        throw ParserException(generic.pos() , properties::Description::NAME + " property can't occurr multiple times");
    if(event.geoProp.size() > 1)
        throw ParserException(generic.pos() , properties::Geo::NAME + " property can't occurr multiple times");
    if(event.lastModifiedProp.size() > 1)
        throw ParserException(generic.pos() , properties::LastModified::NAME + " property can't occurr multiple times");
    if(event.locationProp.size() > 1)
        throw ParserException(generic.pos() , properties::Location::NAME + " property can't occurr multiple times");
    if(event.organizerProp.size() > 1)
        throw ParserException(generic.pos() , properties::Organizer::NAME + " property can't occurr multiple times");
    if(event.priorityProp.size() > 1)
        throw ParserException(generic.pos() , properties::Priority::NAME + " property can't occurr multiple times");
    if(event.sequenceProp.size() > 1)
        throw ParserException(generic.pos() , properties::Sequence::NAME + " property can't occurr multiple times");
    if(event.statusProp.size() > 1)
        throw ParserException(generic.pos() , properties::Status::NAME + " property can't occurr multiple times");
    if(event.summaryProp.size() > 1)
        throw ParserException(generic.pos() , properties::Summary::NAME + " property can't occurr multiple times");
    if(event.transpProp.size() > 1)
        throw ParserException(generic.pos() , properties::Transp::NAME + " property can't occurr multiple times");
    if(event.urlProp.size() > 1)
        throw ParserException(generic.pos() , properties::Url::NAME + " property can't occurr multiple times");
    if(event.recurrenceIdProp.size() > 1)
        throw ParserException(generic.pos() , properties::RecurrenceId::NAME + " property can't occurr multiple times");
    if(event.rruleProp.size() > 1)
        throw ParserException(generic.pos() , properties::RRule::NAME + " property can't occurr multiple times");
    if(event.dtEndProp.size() > 1)
        throw ParserException(generic.pos() , properties::DTEnd::NAME + " property can't occurr multiple times");
    if(event.durationProp.size() > 1)
        throw ParserException(generic.pos() , properties::DurationProp::NAME + " property can't occurr multiple times");
    /* Both DTEND and DURATION can't be present at the same time */
    if(!event.dtEndProp.empty() && !event.durationProp.empty())
        throw ParserException(generic.pos() , properties::DTEnd::NAME + " and " +
                              properties::DurationProp::NAME + " can't be both present");

    if (!uidRegistry.registerId(event.uidProp[0].getValue())) {
        throw ParserException(generic.pos() , "The value of the " + properties::Uid::NAME + " property must be globally unique");
    }

    /* If DTSTART have value DATE then DTEND mmust have value DTEND also */
    /* If duration is specified it must be in dur-day/dur week */
    if(event.dtStartProp.size() == 1) {
        auto & dtStart = event.dtStartProp.at(0);
        if(!dtStart.getValueParam().empty() &&
            dtStart.getValueParam().at(0).getValue() == "DATE") {
            if(!event.dtEndProp.empty()) {
                auto & dtEnd = event.dtEndProp.at(0);
                if(dtEnd.getValueParam().empty() ||
                   dtEnd.getValueParam().at(0).getValue() != "DATE")
                    throw ParserException(generic.pos() , "when DTSTART has value DATE"
                                                          "DTEND must have value DATE too");
            } else if(!event.durationProp.empty()) {
                auto & durVal = event.durationProp.at(0).getValue();
                if(durVal.getHours() != 0 ||
                   durVal.getMinutes() != 0 ||
                   durVal.getSeconds() != 0)
                    throw ParserException(generic.pos() , "when DTSTART has value DATE"
                                                          "DURATION must have value"
                                                          "dur-day or dur-week");
            }
        }
    }

    /* Only following values of STATUS are allowed */
    if(event.statusProp.size() == 1) {
        if(event.statusProp.at(0).getValue() != "TENTATIVE" &&
                event.statusProp.at(0).getValue() != "CONFIRMED" &&
                event.statusProp.at(0).getValue() != "CANCELLED")
            throw ParserException(generic.pos() , "invalid value in STATUS property");
    }

    /* Storing subcomponents */
    for(const auto &i : generic->getSubcomponents()) {
        if(i->getName().value() == components::VAlarm::NAME) {
            event.alarmComps.push_back(components::VAlarm::parse(i));

        } else {
            throw ParserException(i.pos() ,
                                  "invalid component in " + NAME + " component");
        }
    }

    return event;
}

} // namespace components
} // namespace ical

