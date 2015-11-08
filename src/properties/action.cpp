#include "properties/action.h"

namespace ical {
namespace properties {

void Action::print(std::ostream &out) const
{
    out << "ACTION:" << value << "\r\n";
}

Action Action::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The ACTION property must have no parameters!");
    }

    auto &value = generic->getValue();
    if (*value != "AUDIO" && *value != "DISPLAY" && *value != "EMAIL") {
        throw ParserException(value.pos(), "Invalid AUDIO property value!");
    }
    /* force a copy: */
    return { std::string { *value } };
}

} // namespace properties
} // namespace ical

