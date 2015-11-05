#include "parameters/direntryref.h"

#include "core/valueparser.h"

namespace ical {
namespace parameters {

void DirEntryRef::print(std::ostream &out) const
{
    out << ";DIR=\"" << value << "\"";
}

DirEntryRef DirEntryRef::parse(const core::WithPos<core::GenericPropertyParameter> &generic)
{
    if (generic->getName().value() != "DIR") {
        throw ParserException(generic.pos() , "Invalid DIR parameter name!");
    }

    auto &value = generic->getValue();

    DirEntryRef res;
    res.value = std::move(core::ValueParser::parseQuoted(value.pos(), *value));
    core::ValueParser::validateUri(value.pos(), res.value);
    return res;
}

} // namespace parameters
} // namespace ical

