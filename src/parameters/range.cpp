#include "range.h"

namespace ical {
namespace parameters {

const std::string Range::NAME = "RANGE";

void Range::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Range Range::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty parameter");
    /* Only one accepted value */
    /* THISANDPRIOR is deprecated*/
    if(generic->getValue().value() != "THISANDFUTURE")
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    Range range;
    range.value = generic->getValue().value();
    return range;
}

} // namespace parameters
} // namespace ical

