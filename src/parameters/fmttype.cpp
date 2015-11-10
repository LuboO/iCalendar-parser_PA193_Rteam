#include "parameters/fmttype.h"

namespace ical {
namespace parameters {

const std::string FmtType::NAME = "FMTTYPE";

void FmtType::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

FmtType FmtType::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    auto &value = generic->getValue().value();
    if(value.empty())
        throw ParserException(generic.pos() , "empty property");

    const std::regex RE_FMTTYPE {"[a-zA-Z1-9!#$&.+\\-^_]{1,127}/[a-zA-Z1-9!#$&.+\\-^_]{1,127}"};
    if(!std::regex_match(value.begin() , value.end() , RE_FMTTYPE))
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");

    FmtType fmtType;
    fmtType.value = value;
    return fmtType;
}

} // namespace parameters
} // namespace ical

