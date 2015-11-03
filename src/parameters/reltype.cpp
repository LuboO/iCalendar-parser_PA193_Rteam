#include "reltype.h"

namespace ical {
namespace parameters {

void Reltype::print(std::ostream &out) {
    out << ";RELTYPE=" << value;
}

Reltype Reltype::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "RELTYPE")
        throw ParserException(generic.pos() , "invalid RELTYPE parameter name");
    if(generic->getValue().value() != "PARENT" &&  generic->getValue().value() != "CHILD" &&  generic->getValue().value() != "SIBLING")
        throw ParserException(generic->getValue().pos() , "invalid value in RELTYPE parameter");
    Reltype x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical

