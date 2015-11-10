#include "parameters/rsvp.h"

namespace ical {
namespace parameters {

const std::string Rsvp::NAME = "RSVP";

void Rsvp::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Rsvp Rsvp::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "TRUE" && value != "FALSE")
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    Rsvp x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical
