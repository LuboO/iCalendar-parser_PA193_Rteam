#include "properties/rrule.h"

namespace ical {
namespace properties {

void RRule::print(std::ostream &out) const
{
    out << "RRULE:";
    value.print(out);
    out << "\r\n";
}

RRule RRule::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The RRULE property must have no parameters!");
    }

    auto &value = generic->getValue();
    return {
        std::move(data::RecurrenceRule::parse(
                      value.pos(), value->begin(), value->end()))
    };
}

} // namespace properties
} // namespace ical

