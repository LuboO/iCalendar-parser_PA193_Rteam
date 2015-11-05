#include "reltype.h"

namespace ical {
namespace parameters {

void Reltype::print(std::ostream &out) const {
    out << ";RELTYPE=" << value;
}

Reltype Reltype::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "RELTYPE")
        throw ParserException(generic.pos() , "invalid RELTYPE parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "PARENT" &&  value != "CHILD" &&  value != "SIBLING")
        throw ParserException(generic->getValue().pos() , "invalid value in RELTYPE parameter");
    Reltype x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical

