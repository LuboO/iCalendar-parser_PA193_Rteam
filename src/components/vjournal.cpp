#include "components/vjournal.h"

namespace ical {
namespace components {

const std::string VJournal::NAME = "VJOURNAL";

void VJournal::print(std::ostream &out) const {
    out << "BEGIN:" << NAME << "\r\n";
    for(auto &i : dtStampProp) i.print(out);
    for(auto &i : uidProp) i.print(out);
    for(auto &i : classProp) i.print(out);
    for(auto &i : createdProp) i.print(out);
    for(auto &i : dtStartProp) i.print(out);
    for(auto &i : lastModifiedProp) i.print(out);
    for(auto &i : organizerProp) i.print(out);
    for(auto &i : recurrenceIdProp) i.print(out);
    for(auto &i : sequenceProp) i.print(out);
    for(auto &i : statusProp) i.print(out);
    for(auto &i : summaryProp) i.print(out);
    for(auto &i : urlProp) i.print(out);
    for(auto &i : rruleProp) i.print(out);
    for(auto &i : attachProps) i.print(out);
    for(auto &i : attendeeProps) i.print(out);
    for(auto &i : categoriesProps) i.print(out);
    for(auto &i : commentProps) i.print(out);
    for(auto &i : contactProps) i.print(out);
    for(auto &i : descriptionProps) i.print(out);
    for(auto &i : exDateProps) i.print(out);
    for(auto &i : relatedToProps) i.print(out);
    for(auto &i : rDateProps) i.print(out);
    for(auto &i : requestStatusProps) i.print(out);
    out << "END:" << NAME << "\r\n";
}

VJournal VJournal::parse(const core::WithPos<core::GenericComponent> &generic, core::UniqueIdRegistry &uidRegistry) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " component");

    VJournal journal;

    /* Storing properties */
    for(const core::WithPos<core::GenericProperty> &i : generic->getProperties()) {
        if(i->getName().value() == properties::DTStamp::NAME) {
            journal.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if(i->getName().value() == properties::Uid::NAME) {
            journal.uidProp.push_back(properties::Uid::parse(i));
        } else if(i->getName().value() == properties::Class::NAME) {
            journal.classProp.push_back(properties::Class::parse(i));
        } else if(i->getName().value() == properties::Created::NAME) {
            journal.createdProp.push_back(properties::Created::parse(i));
        } else if(i->getName().value() == properties::DTStart::NAME) {
            journal.dtStartProp.push_back(properties::DTStart::parse(i));
        } else if(i->getName().value() == properties::LastModified::NAME) {
            journal.lastModifiedProp.push_back(properties::LastModified::parse(i));
        } else if(i->getName().value() == properties::Organizer::NAME) {
            journal.organizerProp.push_back(properties::Organizer::parse(i));
        } else if(i->getName().value() == properties::RecurrenceId::NAME) {
            journal.recurrenceIdProp.push_back(properties::RecurrenceId::parse(i));
        } else if(i->getName().value() == properties::Sequence::NAME) {
            journal.sequenceProp.push_back(properties::Sequence::parse(i));
        } else if(i->getName().value() == properties::Status::NAME) {
            journal.statusProp.push_back(properties::Status::parse(i));
        } else if(i->getName().value() == properties::Summary::NAME) {
            journal.summaryProp.push_back(properties::Summary::parse(i));
        } else if(i->getName().value() == properties::Url::NAME) {
            journal.urlProp.push_back(properties::Url::parse(i));
        } else if(i->getName().value() == properties::RRule::NAME) {
            journal.rruleProp.push_back(properties::RRule::parse(i));
        } else if(i->getName().value() == properties::Attach::NAME) {
            journal.attachProps.push_back(properties::Attach::parse(i));
        } else if(i->getName().value() == properties::Attendee::NAME) {
            journal.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if(i->getName().value() == properties::Categories::NAME) {
            journal.categoriesProps.push_back(properties::Categories::parse(i));
        } else if(i->getName().value() == properties::Comment::NAME) {
            journal.commentProps.push_back(properties::Comment::parse(i));
        } else if(i->getName().value() == properties::Contact::NAME) {
            journal.contactProps.push_back(properties::Contact::parse(i));
        } else if(i->getName().value() == properties::Description::NAME) {
            journal.descriptionProps.push_back(properties::Description::parse(i));
        } else if(i->getName().value() == properties::ExDate::NAME) {
            journal.exDateProps.push_back(properties::ExDate::parse(i));
        } else if(i->getName().value() == properties::RelatedTo::NAME) {
            journal.relatedToProps.push_back(properties::RelatedTo::parse(i));
        } else if(i->getName().value() == properties::RDate::NAME) {
            journal.rDateProps.push_back(properties::RDate::parse(i));
        } else if(i->getName().value() == properties::RequestStatus::NAME) {
            journal.requestStatusProps.push_back(properties::RequestStatus::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in " + NAME + " component");
        }
    }
    /** Properties sanity checking **/
    /* Required properties check */
    if(journal.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , properties::DTStamp::NAME + " is required once in " + NAME + " component");
    if(journal.uidProp.size() != 1)
        throw ParserException(generic.pos() , properties::Uid::NAME + " is required once in " + NAME + " component");
    /* OPTIONAL properties max ONCE check */
    if(journal.classProp.size() > 1)
        throw ParserException(generic.pos() , properties::Class::NAME + " property can't occurr multiple times");
    if(journal.createdProp.size() > 1)
        throw ParserException(generic.pos() , properties::Created::NAME + " property can't occurr multiple times");
    if(journal.dtStartProp.size() > 1)
        throw ParserException(generic.pos() , properties::DTStart::NAME + " property can't occurr multiple times");
    if(journal.lastModifiedProp.size() > 1)
        throw ParserException(generic.pos() , properties::LastModified::NAME + " property can't occurr multiple times");
    if(journal.organizerProp.size() > 1)
        throw ParserException(generic.pos() , properties::Organizer::NAME + " property can't occurr multiple times");
    if(journal.recurrenceIdProp.size() > 1)
        throw ParserException(generic.pos() , properties::RecurrenceId::NAME + " property can't occurr multiple times");
    if(journal.sequenceProp.size() > 1)
        throw ParserException(generic.pos() , properties::Sequence::NAME + " property can't occurr multiple times");
    if(journal.statusProp.size() > 1)
        throw ParserException(generic.pos() , properties::Status::NAME + " property can't occurr multiple times");
    if(journal.summaryProp.size() > 1)
        throw ParserException(generic.pos() , properties::Summary::NAME + " property can't occurr multiple times");
    if(journal.urlProp.size() > 1)
        throw ParserException(generic.pos() , properties::Url::NAME + " property can't occurr multiple times");

    if (!uidRegistry.registerId(journal.uidProp[0].getValue())) {
        throw ParserException(generic.pos() , "The value of the " + properties::Uid::NAME + " property must be globally unique");
    }

    if(journal.statusProp.size() == 1) {
        if(journal.statusProp.at(0).getValue() != "DRAFT" &&
                journal.statusProp.at(0).getValue() != "FINAL" &&
                journal.statusProp.at(0).getValue() != "CANCELLED")
            throw ParserException(generic.pos() , "invalid value in STATUS property");
    }

    return journal;
}

} // namespace components
} // namespace ical
