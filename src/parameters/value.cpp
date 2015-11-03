#include "value.h"

namespace ical {
namespace parameters {

void Value::print(std::ostream &out) {
    out << ";VALUE=" << value;
}

Value Value::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "VALUE")
        throw ParserException(generic.pos() , "invalid VALUE parameter name");
    std::string value = generic->getValue().value();
    if(value != "BINARY" &&
       value != "BOOLEAN" &&
       value != "CAL-ADDRESS" &&
       value != "DATE-TIME" &&
       value != "DURATION" &&
       value != "FLOAT" &&
       value != "INTEGER" &&
       value != "PERIOD" &&
       value != "RECUR" &&
       value != "TEXT" &&
       value != "TIME" &&
       value != "DATE" &&
       value != "URI" &&
       value != "UTC-OFFSET")
        throw ParserException(generic->getValue().pos() , "invalid value in VALUE parameter");
    Value x;
    x.value = generic->getValue().value();
    return x;
}

} // namespace parameters
} // namespace ical
