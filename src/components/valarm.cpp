#include "valarm.h"

namespace ical {
namespace components {

const std::string VAlarm::NAME = "VALARM";

void VAlarm::print(std::ostream &out) const {
    out << "BEGIN:" << NAME << "\r\n";
    for(auto &i : actionProp) i.print(out);
    for(auto &i : triggerProp) i.print(out);
    for(auto &i : durationProp) i.print(out);
    for(auto &i : repeatProp) i.print(out);
    for(auto &i : attachProp) i.print(out);
    for(auto &i : descriptionProp) i.print(out);
    for(auto &i : summaryProp) i.print(out);
    for(auto &i : attendeeProp) i.print(out);
    out << "END:" << NAME << "\r\n";
}

VAlarm VAlarm::parse(const core::WithPos<core::GenericComponent> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " component");

    VAlarm alarm;

    /* Storing properties */
    for(const core::WithPos<core::GenericProperty> &i : generic->getProperties()) {
        if(i->getName().value() == properties::Action::NAME) {
            alarm.actionProp.push_back(properties::Action::parse(i));
        } else if(i->getName().value() == properties::Trigger::NAME) {
            alarm.triggerProp.push_back(properties::Trigger::parse(i));
        } else if(i->getName().value() == properties::DurationProp::NAME) {
            alarm.durationProp.push_back(properties::DurationProp::parse(i));
        } else if(i->getName().value() == properties::Repeat::NAME) {
            alarm.repeatProp.push_back(properties::Repeat::parse(i));
        } else if(i->getName().value() == properties::Attach::NAME) {
            alarm.attachProp.push_back(properties::Attach::parse(i));
        } else if(i->getName().value() == properties::Description::NAME) {
            alarm.descriptionProp.push_back(properties::Description::parse(i));
        } else if(i->getName().value() == properties::Summary::NAME) {
            alarm.summaryProp.push_back(properties::Summary::parse(i));
        } else if(i->getName().value() == properties::Attendee::NAME) {
            alarm.attendeeProp.push_back(properties::Attendee::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid property in " + NAME + " component");
        }
    }
    return alarm;
}

} // namespace components
} // namespace ical

