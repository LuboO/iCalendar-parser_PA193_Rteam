#include "encoding.h"

namespace ical {
namespace parameters {

void Encoding::print(std::ostream &out) const {
    out << ";ENCODING=" << value;
}

Encoding Encoding::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "ENCODING")
        throw ParserException(generic.pos() , "invalid ENCODING parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "8BIT" && value != "BASE64")
        throw ical::ParserException(generic->getValue().pos() , "invalid ENCODING parameter value");
    Encoding enc;
    enc.value = value;
    return enc;
}

} // namespace parameters
} // namespace ical

