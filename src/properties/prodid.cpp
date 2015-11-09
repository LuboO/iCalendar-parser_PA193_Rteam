#include "prodid.h"

namespace ical {
namespace properties {

const std::string ProdId::NAME = "PRODID";

void ProdId::print(std::ostream &out) const{
    out << NAME << ":" << value << "\r\n";
}

ProdId ProdId::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in " + NAME + " property");

    ProdId prodid;
    prodid.value = generic->getValue().value();
    return prodid;
}

} // namespace properties
} // namespace ical

