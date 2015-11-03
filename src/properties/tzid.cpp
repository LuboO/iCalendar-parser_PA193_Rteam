#include "tzid.h"

namespace ical {
namespace properties {

void TZId::print(std::ostream &out) {
    out << "TZID:" << value << "\r\n";
}

TZId TZId::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZID")
        throw ParserException(generic.pos() , "invalid TZID property name");
    if(generic->getParameters().size() > 0)
        throw ParserException(generic.pos() , "invalid parameters in TZID property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    TZId tzid;
    tzid.value = generic->getValue().value();
    return tzid;
}

} // namespace properties
} // namespace ical

