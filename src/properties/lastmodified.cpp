#include "properties/lastmodified.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string LastModified::NAME = "LAST-MODIFIED";

void LastModified::print(std::ostream &out) const
{
    out << NAME << ":";
    value.print(out);
    out << "\r\n";
}

LastModified LastModified::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    auto dt = std::move(core::ValueParser::parseDateTime(
                            value.pos(), value->begin(), value->end()));
    if (dt.getTime().isLocal()) {
        throw ParserException(value.pos(), "The value of the " + NAME + " property must be in the UTC format!");
    }
    return { std::move(dt) };
}

} // namespace properties
} // namespace ical

