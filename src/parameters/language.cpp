#include "language.h"

namespace ical {
namespace parameters {

const std::string Language::NAME = "LANGUAGE";

void Language::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

Language Language::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty parameter");
    /* Language tag is not verified, any string is accepted! */
    Language lang;
    lang.value = generic->getValue().value();
    return lang;
}

} // namespace parameters
} // namespace ical

