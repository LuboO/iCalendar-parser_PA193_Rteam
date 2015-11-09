#include "properties/repeat.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Repeat::NAME = "REPEAT";

void Repeat::print(std::ostream &out) const
{
    if (count == 0) {
        return;
    }

    out << NAME << ":" << count << "\r\n";
}

Repeat Repeat::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    return {
        /* NOTE: the spec doesn't specify that the value should be non-negative,
         * so it is not checked (even though a negative value doesn't seem
         * to make sense here) */
        core::ValueParser::parseInteger(
                    value.pos(), value->begin(), value->end())
    };
}

} // namespace properties
} // namespace ical

