#include "version.h"

namespace ical {
namespace properties {

void Version::print(std::ostream &out) const {
    out << "VERSION:" << value << "\r\n";
}

Version Version::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "VERSION")
        throw ParserException(generic.pos() , "invalid name in VERSION property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in VERSION property");

    /* Only version 2.0 is allowed according to specification */
    auto val = generic->getValue().value();
    if(val != "2.0")
        throw ParserException(generic.pos() , "invalid VERSION property value");
    Version ver;
    ver.value = val;
    return ver;
}

} // namespace properties
} // namespace ical
