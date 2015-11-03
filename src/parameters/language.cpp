#include "language.h"

namespace ical {
namespace parameters {

void Language::print(std::ostream &out) const {
    out << ";LANGUAGE=" << value;
}

Language Language::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "LANGUAGE")
        throw ParserException(generic.pos() , "invalid LANGUAGE parameter name");
    /* Language tag is not verified, any string is accapted! */
    Language lang;
    lang.value = generic->getValue().value();
    return lang;
}

} // namespace parameters
} // namespace ical

