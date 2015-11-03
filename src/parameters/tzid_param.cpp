#include "tzid_param.h"

namespace ical {
namespace parameters {

void Tzid_param::print(std::ostream &out) {
    out << ";TZID=" << value;
}

Tzid_param Tzid_param::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "TZID")
        throw ParserException(generic.pos() , "invalid TZID parameter name");
    /* tzidparam  = "TZID" "=" [tzidprefix] paramtext ??? */
    Tzid_param x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
