#include "tzoffsetto.h"

namespace ical {
namespace properties {

void TZOffsetTo::print(std::ostream &out) const {
    out << "TZOFFSETTO:";
    value.print(out);
    out << "\r\n";
}

TZOffsetTo TZOffsetTo::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZOFFSETTO")
        throw ParserException(generic.pos() , "invalid name of TZOFFSETTO property");
    if(!generic->getParameters().empty())
            throw ParserException(generic.pos() , "invalid TZOFFSETTO property parameters");

    auto &value = generic->getValue();
    if(value->empty())
        throw ParserException(generic.pos() , "empty property");

    TZOffsetTo tzoffsetto;
    tzoffsetto.value = std::move(
                data::UTCOffset::parse(
                    value.pos(), value->begin(), value->end()));
    return tzoffsetto;
}

} // namespace properties
} // namespace ical

