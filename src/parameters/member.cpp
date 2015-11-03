#include "member.h"

namespace ical {
namespace parameters {

void Member::print(std::ostream &out) const {
    out << ";MEMBER=";
    for(size_t i = 0 ; i < value.size() ; i++) {
        out << "\"" << i << "\"";
        if(i != value.size() - 1)
            out << ",";
    }
}

Member Member::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "MEMBER")
        throw ParserException(generic.pos() , "invalid MEMBER parameter name");
    std::string val = generic->getValue().value();

    /* Only correct format is checked (what is inside quotes doesn't concern me)*/
    /* DQUOTE cal-address DQUOTE *("," DQUOTE cal-address DQUOTE) */
    std::regex RE_VALID {"^\"[^\",]+?\"(:?,\"[^,\"]+?\")*?$"};
    if(!std::regex_match(val.begin() , val.end() , RE_VALID)) {
        throw ParserException(generic->getValue().pos() , "invalid value in MEMBER parameter");
    } else {
        /* Extracting the values inside quotes from the string */
        Member mem;
        std::regex RE_ADDRESSES{"\"([^\",]+?)\""};
        std::sregex_iterator it(val.begin() , val.end() , RE_ADDRESSES);
        std::sregex_iterator end;
        while(it != end) {
            mem.value.push_back(it->str(1));
            ++it;
        }
        return mem;
    }
}

} // namespace parameters
} // namespace ical

