#include "range.h"

namespace ical {
namespace parameters {

void Range::print(std::ostream &out) {
    out << ";RANGE=" << value;
}

Range Range::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "RANGE")
        throw ParserException(generic.pos() , "invalid RANGE parameter name");
    /* Only one accepted value */
    /* THISANDPRIOR is deprecated*/
    if(generic->getValue().value() != "THISANDFUTURE")
        throw ParserException(generic->getValue().pos() , "invalid value in RANGE parameter");
    Range range;
    range.value = generic->getValue().value();
    return range;
}

} // namespace parameters
} // namespace ical

