#include "tzname.h"

namespace ical {
namespace properties {

void TZName::print(std::ostream &out) {
    out << "TZNAME";
    if(langParam.size() > 0)
        langParam[0].print(out);
    out << ":" << value << "\r\n";
}

TZName TZName::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZNAME")
        throw ParserException(generic.pos() , "invalid name in TZNAME property");

    TZName tzname;
    for(const core::WithPos<core::GenericPropertyParameter> & i : generic->getParameters()) {
        if(i->getName().value() == "LANGUAGE") {
            if(tzname.langParam.size() == 0) {
                parameters::Language lang = parameters::Language::parse(i);
                tzname.langParam.push_back(lang);
            } else {
                throw ParserException(generic.pos() ,
                                      "only one parameter in TZNAME is allowed");
            }
        } else {
            throw ParserException(generic.pos() , "invalid parameters in TZNAME property");
        }
    }
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    tzname.value = generic->getValue().value();
    return tzname;
}

} // namespace properties
} // namespace ical

