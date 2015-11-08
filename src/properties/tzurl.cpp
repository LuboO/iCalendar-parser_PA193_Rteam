#include "tzurl.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void TZUrl::print(std::ostream &out) const {
    out << "TZURL:" << value << "\r\n";
}

TZUrl TZUrl::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZURL")
        throw ParserException(generic.pos() , "invalid name in TZURL property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in TZURL property");

    auto &value = generic->getValue();

    core::ValueParser::validateUri(value.pos(), *value);

    TZUrl tzurl;
    tzurl.value = *value;
    return tzurl;
}

} // namespace properties
} // namespace ical

