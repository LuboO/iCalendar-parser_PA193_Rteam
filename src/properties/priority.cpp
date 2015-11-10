#include "priority.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Priority::NAME = "PRIORITY";

void Priority::print(std::ostream &out) const {
    out << NAME << ":" << value << "\r\n";
}

Priority Priority::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    int ival = core::ValueParser::parseInteger(value.pos(), value->begin(), value->end());
    if (ival > 9 || ival < 0) throw ParserException(generic.pos(), "The " + NAME + " property value must be an integer in a range [0,9]!");
    return Priority { ival };
}

} // namespace properties
} // namespace ical

