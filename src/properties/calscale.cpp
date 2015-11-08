#include "calscale.h"

namespace ical {
namespace properties {

void CalScale::print(std::ostream &out) const{
    out << "CALSCALE:" << value << "\r\n";
}

CalScale CalScale::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "CALSCALE")
        throw ParserException(generic.pos() , "invalid name in CALSCALE property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameter in CALSCALE property");

    /* Only value GREGORIAN is defined by current specification */
    auto value = generic->getValue().value();
    if(value != "GREGORIAN")
        throw ParserException(generic.pos() , "invalid value in CALSCALE property");
    CalScale calscale;
    calscale.value = value;
    return calscale;
}

} // namespace properties
} // namespace ical
