#include "tzoffsetfrom.h"

namespace ical {
namespace properties {

void TZOffsetFrom::print(std::ostream &out) const {
    out << "TZOFFSETFROM:";
    value.print(out);
    out << "\r\n";
}

TZOffsetFrom TZOffsetFrom::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZOFFSETFROM")
        throw ParserException(generic.pos() , "invalid name of TZOFFSETFROM property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid TZOFFSETFROM property parameters");

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

