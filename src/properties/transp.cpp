#include "transp.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

void Transp::print(std::ostream &out) const{
    out << "STATUS:" << value << "\r\n";
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
    transp.value = std::move(core::ValueParser::parseText(
                                  value.pos(), value->begin(), value->end()));
    return transp;
}

} // namespace properties
} // namespace ical

