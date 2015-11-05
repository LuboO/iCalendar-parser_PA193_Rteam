#include "role.h"

namespace ical {
namespace parameters {

void Role::print(std::ostream &out) const {
    out << ";ROLE=" << value;
}

Role Role::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "ROLE")
        throw ParserException(generic.pos() , "invalid ROLE parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "CHAIR" &&
            value != "REQ-PARTICIPANT" &&
            value != "OPT-PARTICIPANT" &&
            value != "NON-PARTICIPANT")
        throw ParserException(generic->getValue().pos() , "invalid value in ROLE parameter");
    Role x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical
