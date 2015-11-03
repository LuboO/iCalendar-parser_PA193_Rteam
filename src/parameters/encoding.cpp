#include "encoding.h"

namespace ical {
namespace parameters {

void Encoding::print(std::ostream &out) {
    out << ";ENCODING=" << value;
}

Encoding Encoding::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic.value().getName().value() != "ENCODING")
        throw ParserException(generic.pos() , "invalid ENCODING parameter name");
    if(generic.value().getValue().value() != "8BIT" &&
       generic.value().getValue().value() != "BASE64")
        throw ical::ParserException(generic.pos() , "invalid ENCODING parameter value");
    Encoding enc;
    enc.value = generic->getValue().value();
    return enc;
}

} // namespace parameters
} // namespace ical

