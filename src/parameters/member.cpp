#include "member.h"

namespace ical {
namespace parameters {

void Member::print(std::ostream &out) {
    out << ";MEMBER=" << value;
}

Member Member::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "MEMBER")
        throw ParserException(generic.pos() , "invalid MEMBER parameter name");
    std::string val = generic->getValue().value();

    /* Only correct format is checked (what is inside quotes doesn't concern me)*/
    /* DQUOTE cal-address DQUOTE *("," DQUOTE cal-address DQUOTE) */
    std::regex RE_CAL_ADDRESS {"^\"([^,\"]+?)\"(,\"[^,\"]+?\")*?$"};
    if(!std::regex_match(val.begin() , val.end() , RE_CAL_ADDRESS))
        throw ParserException(generic->getValue().pos() , "invalid value in MEMBER parameter");
    Member mem;
    mem.value = val;
    return mem;
}

} // namespace parameters
} // namespace ical

