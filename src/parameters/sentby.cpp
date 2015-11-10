#include "parameters/sentby.h"

namespace ical {
namespace parameters {

const std::string SentBy::NAME = "SENT-BY";

void SentBy::print(std::ostream &out) const {
    out << ";" << NAME << "=\"" << value << "\"";
}

SentBy SentBy::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty parameter");
    SentBy x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
