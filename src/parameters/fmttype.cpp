#include "fmttype.h"

namespace ical {
namespace parameters {

void FmtType::print(std::ostream &out) const {
    out << ";FMTTYPE=" << value;
}

FmtType FmtType::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "FMTTYPE")
        throw ParserException(generic.pos() , "invalid FMTTYPE parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty property");

    const std::regex RE_FMTTYPE {"[a-zA-Z1-9!#$&.+\\-^_]{1,127}/[a-zA-Z1-9!#$&.+\\-^_]{1,127}"};
    if(!std::regex_match(value.begin() , value.end() , RE_FMTTYPE))
        throw ParserException(generic->getValue().pos() , "invalid value in FMTTYPE parameter");

    FmtType fmtType;
    fmtType.value = value;
    return fmtType;
}

} // namespace parameters
} // namespace ical

