#include "summary.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void Summary::print(std::ostream &out) const{
    out << "SUMMARY";
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

Summary Summary::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "SUMMARY")
        throw ParserException(generic.pos() , "invalid name in SUMMARY property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty SUMMARY property");

    auto &value = generic->getValue();

    Summary summary;
    summary.value = std::move(core::ValueParser::parseText(
                                  value.pos(), value->begin(), value->end()));

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "ALTREP") {
            if(!summary.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      "ALTREP parameter can't occurr multiple times");
            summary.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == "LANGUAGE") {
            if(!summary.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            summary.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid SUMMARY property parameter");
        }
    }
    return summary;
}

} // namespace properties
} // namespace ical

