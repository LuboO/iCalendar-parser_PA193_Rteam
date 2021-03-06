#include "properties/tzname.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string TZName::NAME = "TZNAME";

void TZName::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : languageParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

TZName TZName::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    TZName tzname;
    tzname.value = std::move(core::ValueParser::parseText(
                                 value.pos(), value->begin(), value->end()));

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Language::NAME) {
            if(!tzname.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "parameter " + parameters::Language::NAME + " can't occur multiple times");
            tzname.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(generic.pos() , "invalid parameters in " + NAME + " property");
        }
    }
    return tzname;
}

} // namespace properties
} // namespace ical

