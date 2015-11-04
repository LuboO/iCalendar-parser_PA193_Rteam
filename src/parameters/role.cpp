#include "role.h"

namespace ical {
namespace parameters {

void Role::print(std::ostream &out) const {
    out << ";ROLE=" << value;
}

Role Role::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "ROLE")
        throw ParserException(generic.pos() , "invalid ROLE parameter name");
    if(generic->getValue().value() != "CHAIR" &&  generic->getValue().value() != "REQ-PARTICIPANT" &&
            generic->getValue().value() != "OPT-PARTICIPANT" && generic->getValue().value() != "NON-PARTICIPANT")
        throw ParserException(generic->getValue().pos() , "invalid value in ROLE parameter");
    Role x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
