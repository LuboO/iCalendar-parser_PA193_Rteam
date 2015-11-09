#include "tzid_param.h"

namespace ical {
namespace parameters {

void Tzid_param::print(std::ostream &out) const {
    out << ";TZID=" << value;
}

Tzid_param Tzid_param::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "TZID")
        throw ParserException(generic.pos() , "invalid TZID parameter name");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty parameter");

    auto &value = generic->getValue();

    /* the spec says TZID can only contain 'paramtext' value: */
    if (value->size() != 0 && value->front() == '"') {
        throw ParserException(value.pos() , "The TZID parameter must not contain a quoted value!");
    }

    Tzid_param x;
    x.value = *value;
    return x;
}

} // namespace parameters
} // namespace ical
