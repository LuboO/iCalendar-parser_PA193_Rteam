#include "member.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

void Member::print(std::ostream &out) const {
    out << ";MEMBER=";
    for (size_t i = 0 ; i < value.size() ; i++) {
        if (i != 0) {
            out << ",";
        }
        out << "\"" << value[i] << "\"";
    }
}

Member Member::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if (generic->getName().value() != "MEMBER") {
        throw ParserException(generic.pos() , "invalid MEMBER parameter name");
    }

    Member mem;
    for (auto &value : generic->getValues()) {
        std::string unquoted = std::move(core::ValueParser::parseQuoted(value.pos(), *value));
        core::ValueParser::validateCalendarAddress(value.pos(), unquoted);
        mem.value.emplace_back(std::move(unquoted));
    }
    return mem;
}

} // namespace parameters
} // namespace ical

