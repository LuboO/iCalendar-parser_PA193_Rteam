#include "parameters/reltype.h"

namespace ical {
namespace parameters {

const std::string Reltype::NAME = "RELTYPE";

void Reltype::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Reltype Reltype::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "PARENT" &&  value != "CHILD" &&  value != "SIBLING")
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    Reltype x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical

