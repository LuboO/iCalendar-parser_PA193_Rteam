#include "properties/tzoffsetfrom.h"

namespace ical {
namespace properties {

const std::string TZOffsetFrom::NAME = "TZOFFSETFROM";

void TZOffsetFrom::print(std::ostream &out) const {
    out << NAME << ":";
    value.print(out);
    out << "\r\n";
}

TZOffsetFrom TZOffsetFrom::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name of " + NAME + " property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid " + NAME + " property parameters");

    auto &value = generic->getValue();
    if(value->empty())
        throw ParserException(generic.pos() , "empty property");

    TZOffsetFrom tzoffsetfrom;
    tzoffsetfrom.value = std::move(
                data::UTCOffset::parse(
                    value.pos(), value->begin(), value->end()));
    return tzoffsetfrom;
}

} // namespace properties
} // namespace ical

