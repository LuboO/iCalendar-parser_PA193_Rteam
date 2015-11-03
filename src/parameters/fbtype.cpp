#include "fbtype.h"

namespace ical {
namespace parameters {

void FBType::print(std::ostream &out) const {
    out << ";FBTYPE=" << value;
}

FBType FBType::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "FBTYPE")
        throw ParserException(generic.pos() , "invalid FBTYPE parameter name");
    if(generic->getValue().value() != "FREE" &&
       generic->getValue().value() != "BUSY" &&
       generic->getValue().value() != "BUSY-UNAVAILABLE" &&
       generic->getValue().value() != "BUSY-TENTATIVE" )
        throw ParserException(generic->getValue().pos() , "invalid value in FBTYPE parameter");
    FBType fbtype;
    fbtype.value = generic->getValue().value();
    return fbtype;
}

} // namespace parameters
} // namespace ical

