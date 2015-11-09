#include "parameters/commonname.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

const std::string CommonName::NAME = "CN";

void CommonName::print(std::ostream &out) const
{
    out << ";" << NAME << "=";
    if (value.find_first_of(",;:") != std::string::npos) {
        out << "\"" << value << "\"";
    } else {
        out << value;
    }
}

CommonName CommonName::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != NAME) {
        throw ParserException(generic.pos() , "Invalid " + NAME + " parameter name!");
    }

    auto &value = generic->getValue();

    CommonName res;
    res.value = std::move(core::ValueParser::parsePossiblyQuoted(value.pos(), *value));
    return res;
}

} // namespace parameters
} // namespace ical

