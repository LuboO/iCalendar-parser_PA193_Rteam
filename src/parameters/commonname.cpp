#include "parameters/commonname.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

void CommonName::print(std::ostream &out) const
{
    out << ";CN=";
    if (value.find_first_of(",;:") != std::string::npos) {
        out << "\"" << value << "\"";
    } else {
        out << value;
    }
}

CommonName CommonName::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != "CN") {
        throw ParserException(generic.pos() , "Invalid CN parameter name!");
    }

    auto &value = generic->getValue();

    CommonName res;
    res.value = std::move(core::ValueParser::parsePossiblyQuoted(value.pos(), *value));
    return res;
}

} // namespace parameters
} // namespace ical

