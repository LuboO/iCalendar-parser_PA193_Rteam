#include "parameters/altrep.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

const std::string AltRep::NAME = "ALTREP";

void AltRep::print(std::ostream &out) const
{
    out << ";" << NAME << "=\"" << value << "\"";
}

AltRep AltRep::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != NAME) {
        throw ParserException(generic.pos() , "Invalid " + NAME + " parameter name!");
    }

    auto &value = generic->getValue();

    AltRep res;
    res.value = std::move(core::ValueParser::parseQuoted(value.pos(), *value));
    core::ValueParser::validateUri(value.pos(), res.value);
    return res;
}

} // namespace parameters
} // namespace ical

