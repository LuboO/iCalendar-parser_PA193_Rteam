#include "properties/lastmodified.h"

namespace ical {
namespace properties {

void LastModified::print(std::ostream &out) const
{
    out << "LAST-MODIFIED:";
    value.print(out);
    out << "\r\n";
}

LastModified LastModified::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The LAST-MODIFIED property must have no parameters!");
    }

    auto &value = generic->getValue();
    auto dt = std::move(data::DateTime::parse(
                            value.pos(), value->begin(), value->end()));
    if (dt.getTime().isLocal()) {
        throw ParserException(value.pos(), "The value of the LAST-MODIFIED property must be in the UTC format!");
    }
    return { std::move(dt) };
}

} // namespace properties
} // namespace ical

