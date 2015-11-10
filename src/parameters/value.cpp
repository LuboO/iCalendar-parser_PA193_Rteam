#include "parameters/value.h"

namespace ical {
namespace parameters {

const std::string Value::NAME = "VALUE";

void Value::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Value Value::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    std::string value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty parameter");
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
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    Value x;
    x.value = value;
    return x;
}

} // namespace parameters
} // namespace ical
