#include "properties/transp.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Transp::NAME = "TRANSP";

void Transp::print(std::ostream &out) const{
    out << NAME << ":" << value << "\r\n";
}

Transp Transp::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The TRANSP property must have no parameters!");
    }

    auto &value = generic->getValue();
    if (*value != "OPAQUE" && *value != "TRANSPARENT") {
        throw ParserException(value.pos(), "Invalid TRANSP property value!");
    }
    Transp transp;
    transp.value = *value;
    return transp;
}

} // namespace properties
} // namespace ical

