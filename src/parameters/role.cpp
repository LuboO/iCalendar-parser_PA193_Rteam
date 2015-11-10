#include "parameters/role.h"

namespace ical {
namespace parameters {

const std::string Role::NAME = "ROLE";

void Role::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Role Role::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "CHAIR" &&
            value != "REQ-PARTICIPANT" &&
            value != "OPT-PARTICIPANT" &&
            value != "NON-PARTICIPANT")
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    Role x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical
