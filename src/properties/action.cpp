#include "properties/action.h"

namespace ical {
namespace properties {

const std::string Action::NAME = "ACTION";

void Action::print(std::ostream &out) const
{
    out << NAME << ":" << value << "\r\n";
}

Action Action::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    if (*value != "AUDIO" && *value != "DISPLAY" && *value != "EMAIL") {
        throw ParserException(value.pos(), "Invalid AUDIO property value!");
    }
    /* force a copy: */
    return Action { std::string { *value } };
}

} // namespace properties
} // namespace ical

