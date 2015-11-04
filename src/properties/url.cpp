#include "url.h"

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

    /* URI value is not validated */
    Url url;
    url.value = generic->getValue().value();
    return url;
}

} // namespace properties
} // namespace ical

