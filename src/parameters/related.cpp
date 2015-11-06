#include "related.h"

namespace ical {
namespace parameters {

void Related::print(std::ostream &out) const {
    if (value == "START") {
        return;
    }

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

    return { std::string(value) };
}

} // namespace parameters
} // namespace ical

