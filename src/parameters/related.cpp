#include "related.h"

namespace ical {
namespace parameters {

void Related::print(std::ostream &out) const {
    out << ";RELATED=" << value;
}

Related Related::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "RELATED")
        throw ParserException(generic.pos() , "invalid RELATED parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "START" && value != "END")
        throw ParserException(generic->getValue().pos() , "invalid value in RELATED parameter");
    Related rel;
    rel.value = value;
    return rel;
}

} // namespace parameters
} // namespace ical

