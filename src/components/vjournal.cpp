#include "vjournal.h"

namespace ical {
namespace components {

void VJournal::print(std::ostream &out) const {
    //journal
}

VJournal VJournal::parse(const core::WithPos<core::GenericComponent> &generic) {
    if(generic->getName().value() != "VJOURNAL")
        throw ParserException(generic.pos() , "invalid name in VJOURNAL component");

    VJournal journal;

    /* Storing properties */
    for(const core::WithPos<core::GenericProperty> &i : generic->getProperties()) {
        if(i->getName().value() == "DTSTAMP") {
            journal.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if(i->getName().value() == "UID") {
            journal.uidProp.push_back(properties::Uid::parse(i));
        } else if(i->getName().value() == "CLASS") {
            journal.classProp.push_back(properties::Class::parse(i));
        } else if(i->getName().value() == "CREATED") {
            journal.createdProp.push_back(properties::Created::parse(i));
        } else if(i->getName().value() == "DTSTART") {
            journal.dtStartProp.push_back(properties::Dtstart::parse(i));
        } else if(i->getName().value() == "LAST-MODIFIED") {
            journal.lastModifiedProp.push_back(properties::LastModified::parse(i));
        } else if(i->getName().value() == "ORGANIZER") {
            journal.organizerProp.push_back(properties::Organizer::parse(i));
        } else if(i->getName().value() == "RECURRENCE-ID") {
            journal.recurrenceIdProp.push_back(properties::RecurrenceId::parse(i));
        } else if(i->getName().value() == "SEQUENCE") {
            journal.sequenceProp.push_back(properties::Sequence::parse(i));
        } else if(i->getName().value() == "STATUS") {
            journal.statusProp.push_back(properties::Status::parse(i));
        } else if(i->getName().value() == "SUMMARY") {
            journal.summaryProp.push_back(properties::Summary::parse(i));
        } else if(i->getName().value() == "URL") {
            journal.urlProp.push_back(properties::Url::parse(i));
        } else if(i->getName().value() == "RRULE") {
            journal.rruleProp.push_back(properties::RRule::parse(i));
        } else if(i->getName().value() == "ATTACH") {
            journal.attachProps.push_back(properties::Attach::parse(i));
        } else if(i->getName().value() == "ATTENDEE") {
            journal.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if(i->getName().value() == "CATEGORIES") {
            journal.categoriesProps.push_back(properties::Categories::parse(i));
        } else if(i->getName().value() == "COMMENT") {
            journal.commentProps.push_back(properties::Comment::parse(i));
        } else if(i->getName().value() == "CONTACT") {
            journal.contactProps.push_back(properties::Contact::parse(i));
        } else if(i->getName().value() == "DESCRIPTION") {
            journal.descriptionProps.push_back(properties::Description::parse(i));
        } else if(i->getName().value() == "EXDATE") {
            journal.exDateProps.push_back(properties::ExDate::parse(i));
        } else if(i->getName().value() == "RELATED-TO") {
            journal.relatedToProps.push_back(properties::RelatedTo::parse(i));
        } else if(i->getName().value() == "RDATE") {
            journal.rDateProps.push_back(properties::RDate::parse(i));
        } else if(i->getName().value() == "REQUEST-STATUS") {
            journal.requestStatusProps.push_back(properties::RequestStatus::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in VJOURNAL component");
        }
    }
    /** Properties sanity checking **/
    /* Required properties check */
    if(journal.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , "DTSTAMP is required once in VJOURNAL component");
    if(journal.uidProp.size() != 1)
        throw ParserException(generic.pos() , "UID is required once in VJOURNAL component");
    /* OPTIONAL properties max ONCE check */
    if(journal.classProp.size() > 1)
        throw ParserException(generic.pos() , "CLASS property can't occurr multiple times");
    if(journal.createdProp.size() > 1)
        throw ParserException(generic.pos() , "CREATED property can't occurr multiple times");
    if(journal.dtStartProp.size() > 1)
        throw ParserException(generic.pos() , "DTSTART property can't occurr multiple times");
    if(journal.lastModifiedProp.size() > 1)
        throw ParserException(generic.pos() , "LAST-MODIFIED property can't occurr multiple times");
    if(journal.organizerProp.size() > 1)
        throw ParserException(generic.pos() , "ORGANIZER property can't occurr multiple times");
    if(journal.recurrenceIdProp.size() > 1)
        throw ParserException(generic.pos() , "RECURRENCE-ID property can't occurr multiple times");
    if(journal.sequenceProp.size() > 1)
        throw ParserException(generic.pos() , "SEQUENCE property can't occurr multiple times");
    if(journal.statusProp.size() > 1)
        throw ParserException(generic.pos() , "STATUS property can't occurr multiple times");
    if(journal.summaryProp.size() > 1)
        throw ParserException(generic.pos() , "SUMMARY property can't occurr multiple times");
    if(journal.urlProp.size() > 1)
        throw ParserException(generic.pos() , "URL property can't occurr multiple times");

    //////////////////////////////////////////
    //////////////// TODO ////////////////////
    //////////////////////////////////////////
    /* remaining checks after implementation of DTStart/DTEnd */

    return journal;
}

} // namespace components
} // namespace ical
