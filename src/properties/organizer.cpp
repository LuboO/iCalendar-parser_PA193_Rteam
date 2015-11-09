#include "organizer.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Organizer::NAME = "ORGANIZER";

void Organizer::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : commonNameParam) i.print(out);
    for(auto &i : dirEntryRefParam) i.print(out);
    for(auto &i : sentByParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

Organizer Organizer::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    core::ValueParser::validateCalendarAddress(value.pos(), *value);

    Organizer organizer;
    organizer.value = *value;

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::CommonName::NAME) {
            if(!organizer.commonNameParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::CommonName::NAME + " parameter can't occurr multiple times");
            organizer.commonNameParam.push_back((parameters::CommonName::parse(i)));

        } else if(i->getName().value() == parameters::DirEntryRef::NAME) {
            if(!organizer.dirEntryRefParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::DirEntryRef::NAME + " parameter can't occurr multiple times");
            organizer.dirEntryRefParam.push_back(parameters::DirEntryRef::parse(i));

        } else if(i->getName().value() == parameters::SentBy::NAME) {
            if(!organizer.sentByParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::SentBy::NAME + " parameter can't occurr multiple times");
            organizer.sentByParam.push_back(parameters::SentBy::parse(i));

        } else if(i->getName().value() == parameters::Language::NAME) {
            if(!organizer.languageParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Language::NAME + " parameter can't occurr multiple times");
            organizer.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in " + NAME + " property");
        }
    }
    return organizer;
}

} // namespace properties
} // namespace ical

