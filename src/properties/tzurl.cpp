#include "tzurl.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string TZUrl::NAME = "TZURL";

void TZUrl::print(std::ostream &out) const {
    out << NAME << ":" << value << "\r\n";
}

TZUrl TZUrl::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in " + NAME + " property");

    auto &value = generic->getValue();

    core::ValueParser::validateUri(value.pos(), *value);

    TZUrl tzurl;
    tzurl.value = *value;
    return tzurl;
}

} // namespace properties
} // namespace ical

