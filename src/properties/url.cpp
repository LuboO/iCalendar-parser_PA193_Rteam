#include "properties/url.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Url::NAME = "URL";

void Url::print(std::ostream &out) const {
    out << NAME << ":" << value << "\r\n";
}

Url Url::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameter in " + NAME + " property");

    auto &value = generic->getValue();

    core::ValueParser::validateUri(value.pos(), *value);

    Url url;
    url.value = *value;
    return url;
}

} // namespace properties
} // namespace ical

