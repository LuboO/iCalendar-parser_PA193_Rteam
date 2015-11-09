#include "tzoffsetto.h"

namespace ical {
namespace properties {

const std::string TZOffsetTo::NAME = "TZOFFSETTO";

void TZOffsetTo::print(std::ostream &out) const {
    out << NAME << ":";
    value.print(out);
    out << "\r\n";
}

TZOffsetTo TZOffsetTo::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name of " + NAME + " property");
    if(!generic->getParameters().empty())
            throw ParserException(generic.pos() , "invalid " + NAME + " property parameters");
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

