#include "properties/calscale.h"

namespace ical {
namespace properties {

const std::string CalScale::NAME = "CALSCALE";

void CalScale::print(std::ostream &out) const{
    out << NAME << ":" << value << "\r\n";
}

CalScale CalScale::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameter in " + NAME + " property");

    /* Only value GREGORIAN is defined by current specification */
    auto value = generic->getValue().value();
    if(value != "GREGORIAN")
        throw ParserException(generic.pos() , "invalid value in " + NAME + " property");
    CalScale calscale;
    calscale.value = value;
    return calscale;
}

} // namespace properties
} // namespace ical
