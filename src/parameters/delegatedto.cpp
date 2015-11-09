#include "parameters/delegatedto.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

const std::string DelegatedTo::NAME = "DELEGATED-TO";

void DelegatedTo::print(std::ostream &out) const
{
    out << ";" << NAME << "=";
    for (size_t i = 0 ; i < values.size() ; i++) {
        if (i != 0) {
            out << ",";
        }
        out << "\"" << values[i] << "\"";
    }
}

DelegatedTo DelegatedTo::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != NAME) {
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    }

    DelegatedTo res;
    for (auto &value : generic->getValues()) {
        std::string unquoted = std::move(core::ValueParser::parseQuoted(value.pos(), *value));
        core::ValueParser::validateCalendarAddress(value.pos(), unquoted);
        res.values.emplace_back(std::move(unquoted));
    }
    return res;
}

} // namespace parameters
} // namespace ical

