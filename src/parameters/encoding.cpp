#include "encoding.h"

namespace ical {
namespace parameters {

void Encoding::print(std::ostream &out) const {
    out << ";ENCODING=" << value;
}

Encoding Encoding::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "ENCODING")
        throw ParserException(generic.pos() , "invalid ENCODING parameter name");
    if(generic->getValue().value() != "8BIT" &&
       generic->getValue().value() != "BASE64")
        throw ical::ParserException(generic->getValue().pos() , "invalid ENCODING parameter value");
    Encoding enc;
    enc.value = generic->getValue().value();
    return enc;
}

} // namespace parameters
} // namespace ical

