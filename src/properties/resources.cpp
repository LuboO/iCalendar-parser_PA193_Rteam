#include "properties/resources.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Resources::NAME = "RESOURCES";

void Resources::print(std::ostream &out) const {
    out << "RESOURCES";
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i != 0) {
            out << ",";
        }
        out << values[i];
    }
    out << "\r\n";
}

Resources Resources::parse(const core::WithPos<core::GenericProperty> &generic) {
    auto &value = generic->getValue();

    Resources resources;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::AltRep::NAME) {
            if(!resources.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      "ALTREP parameter can't occurr multiple times");
            resources.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == parameters::AltRep::NAME) {
            if(!resources.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            resources.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid RESOURCES property parameter");
        }
    }

    resources.values = std::move(core::ValueParser::parseDelimitedEscaped(
                                     value.pos(), value->begin(), value->end(),
                                     core::ValueParser::parseText, ','));
    return resources;
}

} // namespace properties
} // namespace ical

