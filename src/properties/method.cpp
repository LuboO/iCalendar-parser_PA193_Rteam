#include "properties/method.h"

#include <regex>

namespace ical {
namespace properties {

const std::string Method::NAME = "METHOD";

void Method::print(std::ostream &out) const{
    out << NAME << ":" << value << "\r\n";
}

Method Method::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in " + NAME + " property");

    /* No methods are defined by iCalendar standard */
    /* All values are accepted (only correct IANA token syntax is checked) */
    static const std::regex RE_IANA_TOKEN { "[-a-zA-Z0-9]+" };
    auto &value = generic->getValue();

    if (!std::regex_match(*value, RE_IANA_TOKEN))
        throw ParserException(value.pos(), "Invalid IANA token!");

    Method method;
    method.value = *value;
    return method;
}

} // namespace properties
} // namespace ical

