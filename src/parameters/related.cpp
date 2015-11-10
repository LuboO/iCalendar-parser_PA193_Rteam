#include "related.h"

namespace ical {
namespace parameters {

const std::string Related::NAME = "RELATED";

void Related::print(std::ostream &out) const {
    if (value == "START") {
        return;
    }

    out << ";" << NAME << "=" << value;
}

Related Related::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "START" && value != "END")
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");

    return Related { std::string(value) };
}

} // namespace parameters
} // namespace ical

