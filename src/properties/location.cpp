#include "location.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void Location::print(std::ostream &out) const {
    out << "LOCATION";
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

Location Location::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "LOCATION")
        throw ParserException(generic.pos() , "invalid name in LOCATION property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty LOCATION property");

    auto &value = generic->getValue();

    Location location;
    location.value = std::move(core::ValueParser::parseText(
                                   value.pos(), value->begin(), value->end()));
    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "ALTREP") {
            if(!location.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      "ALTREP parameter can't occurr multiple times");
            location.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == "LANGUAGE") {
            if(!location.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            location.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid LOCATION property parameter");
        }
    }
    return location;
}

} // namespace properties
} // namespace ical

