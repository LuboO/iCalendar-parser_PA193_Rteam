#include "parameters/fbtype.h"

namespace ical {
namespace parameters {

const std::string FBType::NAME = "FBTYPE";

void FBType::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

FBType FBType::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
    if(value != "FREE" && value != "BUSY" && value != "BUSY-UNAVAILABLE" &&
            value != "BUSY-TENTATIVE" )
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    FBType fbtype;
    fbtype.value = value;
    return fbtype;
}

} // namespace parameters
} // namespace ical

