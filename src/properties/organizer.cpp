#include "organizer.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void Organizer::print(std::ostream &out) const {
    out << "ORGANIZER";
    for(auto &i : commonNameParam) i.print(out);
    for(auto &i : dirEntryRefParam) i.print(out);
    for(auto &i : sentByParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

Organizer Organizer::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "ORGANIZER")
        throw ParserException(generic.pos() , "invalid name in ORGANIZER property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    core::ValueParser::validateCalendarAddress(value.pos(), *value);

    Organizer organizer;
    organizer.value = *value;

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == "CN") {
            if(!organizer.commonNameParam.empty())
                throw ParserException(i.pos() ,
                                      "CN parameter can't occurr multiple times");
            organizer.dirEntryRefParam.push_back((parameters::DirEntryRef::parse(i)));

        } else if(i->getName().value() == "DIR") {
            if(!organizer.dirEntryRefParam.empty())
                throw ParserException(i.pos() ,
                                      "DIR parameter can't occurr multiple times");
            organizer.dirEntryRefParam.push_back(parameters::DirEntryRef::parse(i));

        } else if(i->getName().value() == "SENT-BY") {
            if(!organizer.sentByParam.empty())
                throw ParserException(i.pos() ,
                                      "SENT-BY parameter can't occurr multiple times");
            organizer.sentByParam.push_back(parameters::SentBy::parse(i));

        } else if(i->getName().value() == "LANGUAGE") {
            if(!organizer.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            organizer.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in ORGANIZER property");
        }
    }
    return organizer;
}

} // namespace properties
} // namespace ical

