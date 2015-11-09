#include "parameters/calusertype.h"

namespace ical {
namespace parameters {

const std::string CalUserType::NAME = "CUTYPE";

void CalUserType::print(std::ostream &out) const
{
    out << ";" << NAME << "=" << value;
}

CalUserType CalUserType::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != NAME) {
        throw ParserException(generic.pos() , "Invalid " + NAME + " parameter name!");
    }

    auto &value = generic->getValue();
    if (*value != "INDIVIDUAL" && *value != "GROUP" && *value != "RESOURCE" &&
            *value != "ROOM" && *value != "UNKNOWN") {
        throw ParserException(value.pos(), "Invalid " + NAME + " parameter value!");
    }

    CalUserType res;
    res.value = *value;
    return res;
}

} // namespace parameters
} // namespace ical

