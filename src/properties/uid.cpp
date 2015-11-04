#include "uid.h"

namespace ical {
namespace properties {

void Uid::print(std::ostream &out) const {
    out << "UID:" << value << "\r\n";
}

Uid Uid::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "UID")
        throw ParserException(generic.pos() , "invalid name id UID property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameter in UID property");

    /* this should be unique... how to achieve that? :D */
    Uid uid;
    uid.value = generic->getValue().value();
    return uid;
}

} // namespace properties
} // namespace ical

