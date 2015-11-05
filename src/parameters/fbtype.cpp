#include "fbtype.h"

namespace ical {
namespace parameters {

void FBType::print(std::ostream &out) const {
    out << ";FBTYPE=" << value;
}

FBType FBType::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "FBTYPE")
        throw ParserException(generic.pos() , "invalid FBTYPE parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "FREE" && value != "BUSY" && value != "BUSY-UNAVAILABLE" &&
            value != "BUSY-TENTATIVE" )
        throw ParserException(generic->getValue().pos() , "invalid value in FBTYPE parameter");
    FBType fbtype;
    fbtype.value = value;
    return fbtype;
}

} // namespace parameters
} // namespace ical

