#include "sentby.h"

namespace ical {
namespace parameters {

void SentBy::print(std::ostream &out) const {
    out << ";SENT-BY=\"" << value << "\"";
}

SentBy SentBy::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "SENT-BY")
        throw ParserException(generic.pos() , "invalid SENT-BY parameter name");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty parameter");
    SentBy x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
