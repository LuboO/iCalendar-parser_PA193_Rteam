#include "tzname.h"

namespace ical {
namespace properties {

void TZName::print(std::ostream &out) const {
    out << "TZNAME";
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

TZName TZName::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZNAME")
        throw ParserException(generic.pos() , "invalid name in TZNAME property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    TZName tzname;
    tzname.value = generic->getValue().value();

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == "LANGUAGE") {
            if(!tzname.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "parameter LANGUAGE can't occur multiple times");
            tzname.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(generic.pos() , "invalid parameters in TZNAME property");
        }
    }
    return tzname;
}

} // namespace properties
} // namespace ical

