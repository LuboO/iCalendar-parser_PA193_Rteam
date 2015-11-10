#include "properties/tzid.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string TZId::NAME = "TZID";

void TZId::print(std::ostream &out) const {
    out << NAME << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

TZId TZId::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " property name");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    auto &value = generic->getValue();

    TZId tzid;
    tzid.value = std::move(core::ValueParser::parseText(
                               value.pos(), value->begin(), value->end()));
    return tzid;
}

} // namespace properties
} // namespace ical

