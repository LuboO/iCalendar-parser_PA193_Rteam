#include "sentby.h"

namespace ical {
namespace parameters {

void SentBy::print(std::ostream &out) {
    out << ";SENT-BY=" << value;
}

SentBy SentBy::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "SENT-BY")
        throw ParserException(generic.pos() , "invalid SENT-BY parameter name");
    std::regex RE_CAL_ADDRESS {"^\"([^,\"]+?)\"$"};
    if(!std::regex_match(generic->getValue().value().begin() , generic->getValue().value().end() , RE_CAL_ADDRESS))
        throw ParserException(generic->getValue().pos() , "invalid value in SENT- BY parameter");
    SentBy x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
