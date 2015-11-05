#include "parameters/delegatedfrom.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

void DelegatedFrom::print(std::ostream &out) const
{
    out << ";DELEGATED-FROM=";
    for (size_t i = 0 ; i < values.size() ; i++) {
        if (i != 0) {
            out << ",";
        }
        out << "\"" << values[i] << "\"";
    }
}

DelegatedFrom DelegatedFrom::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != "DELEGATED-FROM") {
        throw ParserException(generic.pos() , "invalid DELEGATED-FROM parameter name");
    }

    DelegatedFrom res;
    for (auto &value : generic->getValues()) {
        std::string unquoted = std::move(core::ValueParser::parseQuoted(value.pos(), *value));
        core::ValueParser::validateCalendarAddress(value.pos(), unquoted);
        res.values.emplace_back(std::move(unquoted));
    }
    return res;
}

} // namespace parameters
} // namespace ical

