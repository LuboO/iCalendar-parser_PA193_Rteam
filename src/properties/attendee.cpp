#include "properties/attendee.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Attendee::NAME = "ATTENDEE";

void Attendee::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : calUserTypeParam) i.print(out);
    for(auto &i : memberParam) i.print(out);
    for(auto &i : roleParam) i.print(out);
    for(auto &i : partStatParam) i.print(out);
    for(auto &i : rsvpParam) i.print(out);
    for(auto &i : delegatedToParam) i.print(out);
    for(auto &i : delegatedFromParam) i.print(out);
    for(auto &i : sentByParam) i.print(out);
    for(auto &i : commonNameParam) i.print(out);
    for(auto &i : dirEntryRefParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

Attendee Attendee::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    core::ValueParser::validateCalendarAddress(value.pos(), *value);

    Attendee attendee;
    attendee.value = *value;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::CalUserType::NAME) {
            if(!attendee.calUserTypeParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::CalUserType::NAME + " parameter can't occurr multiple times");
            attendee.calUserTypeParam.push_back(parameters::CalUserType::parse(i));

        } else if(i->getName().value() == parameters::Member::NAME) {
            if(!attendee.memberParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Member::NAME + " parameter can't occur multiple times");
            attendee.memberParam.push_back(parameters::Member::parse(i));

        } else if(i->getName().value() == parameters::Role::NAME) {
            if(!attendee.roleParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Role::NAME + " parameter can't occur multiple times");
            attendee.roleParam.push_back(parameters::Role::parse(i));

        } else if(i->getName().value() == parameters::PartStat::NAME) {
            if(!attendee.partStatParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::PartStat::NAME + " parameter can't occur multiple times");
            attendee.partStatParam.push_back(parameters::PartStat::parse(i));

        } else if(i->getName().value() == parameters::Rsvp::NAME) {
            if(!attendee.rsvpParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Rsvp::NAME + " parameter can't occur multiple times");
            attendee.rsvpParam.push_back(parameters::Rsvp::parse(i));

        } else if(i->getName().value() == parameters::DelegatedTo::NAME) {
            if(!attendee.delegatedToParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::DelegatedTo::NAME + " parameter can't occurr multiple times");
            attendee.delegatedToParam.push_back(parameters::DelegatedTo::parse(i));

        } else if(i->getName().value() == parameters::DelegatedFrom::NAME) {
            if(!attendee.delegatedFromParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::DelegatedFrom::NAME + " parameter can't occurr multiple times");
            attendee.delegatedFromParam.push_back(parameters::DelegatedFrom::parse(i));

        } else if(i->getName().value() == parameters::SentBy::NAME) {
            if(!attendee.sentByParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::SentBy::NAME + " parameter can't occur multiple times");
            attendee.sentByParam.push_back(parameters::SentBy::parse(i));

        } else if(i->getName().value() == parameters::CommonName::NAME) {
            if(!attendee.commonNameParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::CommonName::NAME + " parameter can't occurr multiple times");
            attendee.commonNameParam.push_back(parameters::CommonName::parse(i));

        } else if(i->getName().value() == parameters::DirEntryRef::NAME) {
            if(!attendee.dirEntryRefParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::DirEntryRef::NAME + " parameter can't occurr multiple times");
            attendee.dirEntryRefParam.push_back(parameters::DirEntryRef::parse(i));

        } else if(i->getName().value() == parameters::Language::NAME) {
            if(!attendee.languageParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Language::NAME + " parameter can't occur multiple times");
            attendee.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid " + NAME + " property parameter");
        }
    }
    return attendee;
}

} // namespace properties
} // namespace ical

