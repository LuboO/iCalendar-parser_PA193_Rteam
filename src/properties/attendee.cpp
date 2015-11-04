#include "attendee.h"

namespace ical {
namespace properties {

void Attendee::print(std::ostream &out) const {
    out << "ATTENDEE";
    //for(auto &i : cuTypeParam) i.print(out);
    for(auto &i : memberParam) i.print(out);
    for(auto &i : roleParam) i.print(out);
    for(auto &i : partStatParam) i.print(out);
    for(auto &i : rsvpParam) i.print(out);
    //for(auto &i : delegatedToParam) i.print(out);
    //for(auto &i : delegateFromParam) i.print(out);
    for(auto &i : sentByParam) i.print(out);
    //for(auto &i : cnParam) i.print(out);
    //for(auto &i : dirParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

Attendee Attendee::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "ATTENDEE")
        throw ParserException(generic.pos() , "invalid name in ATTENDEE property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    Attendee attendee;
    attendee.value = generic->getValue().value();

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "CUTYPE") {
            // wait for implementation
        } else if(i->getName().value() == "MEMBER") {
            if(!attendee.memberParam.empty())
                throw ParserException(i.pos() ,
                                      "MEMBER parameter can't occur multiple times");
            attendee.memberParam.push_back(parameters::Member::parse(i));
        } else if(i->getName().value() == "ROLE") {
            if(!attendee.roleParam.empty())
                throw ParserException(i.pos() ,
                                      "ROLE parameter can't occur multiple times");
            attendee.roleParam.push_back(parameters::Role::parse(i));
        } else if(i->getName().value() == "PARTSTAT") {
            if(!attendee.partStatParam.empty())
                throw ParserException(i.pos() ,
                                      "PARSTAT parameter can't occur multiple times");
            attendee.partStatParam.push_back(parameters::PartStat::parse(i));
        } else if(i->getName().value() == "RSVP") {
            if(!attendee.rsvpParam.empty())
                throw ParserException(i.pos() ,
                                      "RSVP parameter can't occur multiple times");
            attendee.rsvpParam.push_back(parameters::Rsvp::parse(i));
        } else if(i->getName().value() == "DELEGATED-TO") {
            // wait for implementation
        } else if(i->getName().value() == "DELEGATED-FROM") {
            // wait for implementation
        } else if(i->getName().value() == "SENT-BY") {
            if(!attendee.sentByParam.empty())
                throw ParserException(i.pos() ,
                                      "SENT-BY parameter can't occur multiple times");
            attendee.sentByParam.push_back(parameters::SentBy::parse(i));
        } else if(i->getName().value() == "CN") {
            // wait for implementation
        } else if(i->getName().value() == "DIR") {
            // wait for implementation
        } else if(i->getName().value() == "LANGUAGE") {
            if(!attendee.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occur multiple times");
            attendee.languageParam.push_back(parameters::Language::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid ATTENDEE property parameter");
        }
    }
    return attendee;
}

} // namespace properties
} // namespace ical

