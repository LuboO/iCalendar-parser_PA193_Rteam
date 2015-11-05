#include "relatedto.h"

namespace ical {
namespace properties {

void RelatedTo::print(std::ostream &out) const {
    out << "RELATED-TO";
    for(auto &i : reltypeParam) i.print(out);
    out << ":" << value << "\r\n";
}

RelatedTo RelatedTo::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "RELATED-TO")
        throw ParserException(generic.pos() , "invalid name in RELATED-TO property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    RelatedTo relto;
    relto.value = generic->getValue().value();

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == "RELTYPE") {
            if(!relto.reltypeParam.empty())
                throw ParserException(i.pos() ,
                                      "RELTYPE parameter can't occurr multiple times");
            relto.reltypeParam.push_back(parameters::Reltype::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in RELATED-TO property");
        }
    }
    return relto;
}

} // namespace properties
} // namespace ical

