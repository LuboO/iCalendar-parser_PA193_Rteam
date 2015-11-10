#include "vfreebusy.h"

namespace ical {
namespace components {

const std::string VFreeBusy::NAME = "VFREEBUSY";

void VFreeBusy::print(std::ostream &out) const {
    out << "BEGIN:" << NAME << "\r\n";
    for(auto &i : dtStampProp) i.print(out);
    for(auto &i : uidProp) i.print(out);
    for(auto &i : contactProp) i.print(out);
    for(auto &i : dtStartProp) i.print(out);
    for(auto &i : dtendProp) i.print(out);
    for(auto &i : organizerProp) i.print(out);
    for(auto &i : urlProp) i.print(out);
    for(auto &i : attendeeProps) i.print(out);
    for(auto &i : commentProps) i.print(out);
    for(auto &i : freebusyProps) i.print(out);
    out << "END:" << NAME << "\r\n";
}

VFreeBusy VFreeBusy::parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &uidRegistry)
{
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " component");

    VFreeBusy freebusy;

    /* Storing properties */
    for(const core::WithPos<core::GenericProperty> &i : generic->getProperties()) {
        if(i->getName().value() == properties::DTStamp::NAME) {
            freebusy.dtStampProp.push_back(properties::DTStamp::parse(i));
        } else if(i->getName().value() == properties::Uid::NAME) {
            freebusy.uidProp.push_back(properties::Uid::parse(i));
        } else if(i->getName().value() == properties::Contact::NAME) {
            freebusy.contactProp.push_back(properties::Contact::parse(i));
        } else if(i->getName().value() == properties::DTStart::NAME) {
            freebusy.dtStartProp.push_back(properties::DTStart::parse(i));
        } else if(i->getName().value() == properties::DTEnd::NAME) {
            freebusy.dtendProp.push_back(properties::DTEnd::parse(i));
        } else if(i->getName().value() == properties::Organizer::NAME) {
            freebusy.organizerProp.push_back(properties::Organizer::parse(i));
        } else if(i->getName().value() == properties::Url::NAME) {
            freebusy.urlProp.push_back(properties::Url::parse(i));
        } else if(i->getName().value() == properties::Attendee::NAME) {
            freebusy.attendeeProps.push_back(properties::Attendee::parse(i));
        } else if(i->getName().value() == properties::Comment::NAME) {
            freebusy.commentProps.push_back(properties::Comment::parse(i));
        } else if(i->getName().value() == properties::Freebusy::NAME) {
            freebusy.freebusyProps.push_back(properties::Freebusy::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid property in " + NAME + " component");
        }
    }

    /** Properties sanity checking **/
    /* Required properties check */
    if(freebusy.dtStampProp.size() != 1)
        throw ParserException(generic.pos() , properties::DTStamp::NAME + " is required once in " + NAME + " component");
    if(freebusy.uidProp.size() != 1)
        throw ParserException(generic.pos() , properties::Uid::NAME + " is required once in " + NAME + " component");
    /* OPTIONAL properties max ONCE check */
    if(freebusy.contactProp.size() > 1)
        throw ParserException(generic.pos() , properties::Contact::NAME + " property can't occurr multiple times");
    if(freebusy.dtStartProp.size() > 1)
        throw ParserException(generic.pos() , properties::DTStart::NAME + " property can't occurr multiple times");
    if(freebusy.dtendProp.size() > 1)
        throw ParserException(generic.pos() , properties::DTEnd::NAME + " property can't occurr multiple times");
    if(freebusy.organizerProp.size() > 1)
        throw ParserException(generic.pos() , properties::Organizer::NAME + " property can't occurr multiple times");
    if(freebusy.urlProp.size() > 1)
        throw ParserException(generic.pos() , properties::Url::NAME + " property can't occurr multiple times");

    if (!uidRegistry.registerId(freebusy.uidProp[0].getValue())) {
        throw ParserException(generic.pos() , "The value of the " + properties::Uid::NAME + " property must be globally unique");
    }

    return freebusy;

}


} // namespace components
} // namespace ical

