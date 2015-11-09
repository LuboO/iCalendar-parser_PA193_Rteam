#include "encoding.h"

namespace ical {
namespace parameters {

const std::string Encoding::NAME = "ENCODING";

void Encoding::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Encoding Encoding::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "8BIT" && value != "BASE64")
        throw ical::ParserException(generic->getValue().pos() , "invalid " + NAME + " parameter value");
    Encoding enc;
    enc.value = value;
    return enc;
}

} // namespace parameters
} // namespace ical

