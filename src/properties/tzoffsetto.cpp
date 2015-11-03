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
    if(generic->getParameters().size() != 0)
            throw ParserException(generic.pos() , "invalid TZOFFSETTO property parameters");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    TZOffsetTo tzoffsetto;
    data::UTCOffset offset;
    offset = core::ValueParser::parseUTCOffset(generic->getValue().pos() ,
                                               generic->getValue()->begin() ,
                                               generic->getValue()->end());
    tzoffsetto.value = offset;
    return tzoffsetto;
}

} // namespace properties
} // namespace ical

