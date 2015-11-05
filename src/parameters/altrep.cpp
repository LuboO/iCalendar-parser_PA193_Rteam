#include "parameters/altrep.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

void AltRep::print(std::ostream &out) const
{
    out << ";ALTREP=\"" << value << "\"";
}

AltRep AltRep::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != "ALTREP") {
        throw ParserException(generic.pos() , "Invalid ALTREP parameter name!");
    }

    auto &value = generic->getValue();

    AltRep res;
    res.value = std::move(core::ValueParser::parseQuoted(value.pos(), *value));
    core::ValueParser::validateUri(value.pos(), res.value);
    return res;
}

} // namespace parameters
} // namespace ical

