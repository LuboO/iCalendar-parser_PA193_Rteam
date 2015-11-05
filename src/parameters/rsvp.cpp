#include "rsvp.h"

namespace ical {
namespace parameters {

void Rsvp::print(std::ostream &out) const {
    out << ";RSVP=" << value;
}

Rsvp Rsvp::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "RSVP")
        throw ParserException(generic.pos() , "invalid RSVP parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "TRUE" && value != "FALSE")
        throw ParserException(generic->getValue().pos() , "invalid value in RSVP parameter");
    Rsvp x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical
