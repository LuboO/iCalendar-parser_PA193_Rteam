#include "tzoffsetfrom.h"

namespace ical {
namespace properties {

void TZOffsetFrom::print(std::ostream &out) {
    out << "TZOFFSETFROM:";
    value.print(out);
    out << "\r\n";
}

TZOffsetFrom TZOffsetFrom::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "TZOFFSETFROM")
        throw ParserException(generic.pos() , "invalid name of TZOFFSETFROM property");
    if(generic->getParameters().size() != 0)
        throw ParserException(generic.pos() , "invalid TZOFFSETFROM property parameters");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    TZOffsetFrom tzoffsetfrom;
    data::UTCOffset offset;
    offset = core::ValueParser::parseUTCOffset(generic->getValue().pos() ,
                                               generic->getValue()->begin() ,
                                               generic->getValue()->end());
    tzoffsetfrom.value = offset;
    return tzoffsetfrom;
}

} // namespace properties
} // namespace ical

