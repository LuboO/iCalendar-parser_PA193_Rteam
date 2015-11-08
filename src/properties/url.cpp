#include "url.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void Url::print(std::ostream &out) const {
    out << "URL:" << value << "\r\n";
}

Url Url::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "URL")
        throw ParserException(generic.pos() , "invalid name in URL property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameter in URL property");

    auto &value = generic->getValue();

    core::ValueParser::validateUri(value.pos(), *value);

    Url url;
    url.value = *value;
    return url;
}

} // namespace properties
} // namespace ical

