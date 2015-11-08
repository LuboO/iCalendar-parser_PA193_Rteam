#include "method.h"

namespace ical {
namespace properties {

void Method::print(std::ostream &out) const{
    out << "METHOD:" << value << "\r\n";
}

Method Method::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "METHOD")
        throw ParserException(generic.pos() , "invalid name in METHOD property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in METHOD property");

    /* No methods are defined by iCalendar standard */
    /* All values are accepted and value is not validated */
    Method method;
    method.value = generic->getValue().value();
    return method;
}

} // namespace properties
} // namespace ical

