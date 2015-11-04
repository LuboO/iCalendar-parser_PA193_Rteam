#include "tzurl.h"

namespace ical {
namespace properties {

void TZUrl::print(std::ostream &out) const {
    out << "TZURL:" << value << "\r\n";
}

TZUrl TZUrl::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZURL")
        throw ParserException(generic.pos() , "invalid name in TZURL property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in TZURL property");
    /* URI is not parsed and validated */
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty property value");
    TZUrl tzurl;
    tzurl.value = value;
    return tzurl;
}

} // namespace properties
} // namespace ical

