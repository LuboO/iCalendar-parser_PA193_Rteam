#include "completed.h"

namespace ical {
namespace properties {

const std::string Completed::NAME = "COMPLETED";

void Completed::print(std::ostream &out) const
{
    out << "COMPLETED:";
    value.print(out);
    out << "\r\n";
}

Completed Completed::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The COMPLETED property must have no parameters!");
    }

    auto &value = generic->getValue();

    Completed completed;
    completed.value = std::move(
                data::DateTime::parse(
                    value.pos(), value->begin(), value->end()));
    if (completed.value.getTime().isLocal()) {
        throw ParserException(
                    value.pos(),
                    "The value of the COMPLETED property must be in the UTC format!");
    }

    return completed;
}

} // namespace properties
} // namespace ical

