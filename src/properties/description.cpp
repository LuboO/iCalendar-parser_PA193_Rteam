#include "properties/description.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Description::NAME = "DESCRIPTION";

void Description::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

Description Description::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty " + NAME + " property");

    auto &value = generic->getValue();

    Description description;
    description.value = std::move(core::ValueParser::parseText(
                                      value.pos(), value->begin(), value->end()));
    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::AltRep::NAME) {
            if(!description.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::AltRep::NAME + " parameter can't occurr multiple times");
            description.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == parameters::Language::NAME) {
            if(!description.languageParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Language::NAME + " parameter can't occurr multiple times");
            description.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid " + NAME + " property parameter");
        }
    }
    return description;
}

} // namespace properties
} // namespace ical

