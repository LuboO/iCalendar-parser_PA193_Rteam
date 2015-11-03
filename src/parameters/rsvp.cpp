#include "rsvp.h"

namespace ical {
namespace parameters {

void Rsvp::print(std::ostream &out) {
    out << ";RSVP=" << value;
}

Rsvp Rsvp::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "RSVP")
        throw ParserException(generic.pos() , "invalid RSVP parameter name");
    if(generic->getValue().value() != "TRUE" && generic->getValue().value() != "FALSE")
        throw ParserException(generic->getValue().pos() , "invalid value in RSVP parameter");
    Rsvp x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
