#include "properties/created.h"

namespace ical {
namespace properties {

void Created::print(std::ostream &out) const
{
    out << "CREATED:";
    value.print(out);
    out << "\r\n";
}

Created Created::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The CREATED property must have no parameters!");
    }

    auto &value = generic->getValue();
    auto dt = std::move(data::DateTime::parse(
                            value.pos(), value->begin(), value->end()));
    if (dt.getTime().isLocal()) {
        throw ParserException(value.pos(), "The value of the CREATED property must be in the UTC format!");
    }
    return { std::move(dt) };
}

} // namespace properties
} // namespace ical

