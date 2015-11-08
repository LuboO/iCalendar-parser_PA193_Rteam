#include "tzid.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void TZId::print(std::ostream &out) const {
    out << "TZID:" << core::ValueParser::encodeText(value) << "\r\n";
}

TZId TZId::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZID")
        throw ParserException(generic.pos() , "invalid TZID property name");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameters in TZID property");
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

