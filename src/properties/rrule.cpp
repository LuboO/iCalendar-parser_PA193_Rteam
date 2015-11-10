#include "properties/rrule.h"

namespace ical {
namespace properties {

const std::string RRule::NAME = "RRULE";

void RRule::print(std::ostream &out) const
{
    out << NAME << ":";
    value.print(out);
    out << "\r\n";
}

RRule RRule::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    return RRule {
        std::move(data::RecurrenceRule::parse(
                      value.pos(), value->begin(), value->end()))
    };
}

} // namespace properties
} // namespace ical

