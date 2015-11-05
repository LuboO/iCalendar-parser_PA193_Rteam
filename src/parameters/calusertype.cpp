#include "parameters/calusertype.h"

namespace ical {
namespace parameters {

void CalUserType::print(std::ostream &out) const
{
    out << ";CUTYPE=" << value;
}

CalUserType CalUserType::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != "CUTYPE") {
        throw ParserException(generic.pos() , "Invalid CUTYPE parameter name!");
    }

    auto &value = generic->getValue();
    if (*value != "INDIVIDUAL" && *value != "GROUP" && *value != "RESOURCE" &&
            *value != "ROOM" && *value != "UNKNOWN") {
        throw ParserException(value.pos(), "Invalid CUTYPE parameter value!");
    }

    CalUserType res;
    res.value = *value;
    return res;
}

} // namespace parameters
} // namespace ical

