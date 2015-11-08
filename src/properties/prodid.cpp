#include "prodid.h"

namespace ical {
namespace properties {

void ProdId::print(std::ostream &out) const{
    out << "PRODID:" << value << "\r\n";
}

ProdId ProdId::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "PRODID")
        throw ParserException(generic.pos() , "invalid name in PRODID property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in PRODID property");

    ProdId prodid;
    prodid.value = generic->getValue().value();
    return prodid;
}

} // namespace properties
} // namespace ical

