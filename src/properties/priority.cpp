#include "priority.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

void Priority::print(std::ostream &out) const {
    out << "PRIORITY:" << value << "\r\n";
}

Priority Priority::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The PRIORITY property must have no parameters!");
    }

    auto &value = generic->getValue();
    Priority priority;
    priority.value = std::move(core::ValueParser::parseInteger(value.pos(), value->begin(), value->end()));
    if (priority.value > 9 || priority.value < 0) throw ParserException(generic.pos(), "The PRIORITY property value must be an integer in a range [0,9]!");
    return priority;
}

} // namespace properties
} // namespace ical

