#include "properties/relatedto.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string RelatedTo::NAME = "RELATED-TO";

void RelatedTo::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : reltypeParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

RelatedTo RelatedTo::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    RelatedTo relto;
    relto.value = std::move(core::ValueParser::parseText(
                                value.pos(), value->begin(), value->end()));

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Reltype::NAME) {
            if(!relto.reltypeParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Reltype::NAME + " parameter can't occurr multiple times");
            relto.reltypeParam.push_back(parameters::Reltype::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in " + NAME + " property");
        }
    }
    return relto;
}

} // namespace properties
} // namespace ical

