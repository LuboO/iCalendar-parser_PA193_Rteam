#include "status.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Status::NAME = "STATUS";

void Status::print(std::ostream &out) const {
    out << NAME << ":" << value << "\r\n";
}

Status Status::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    if (*value != "TENTATIVE" && *value != "CONFIRMED"
            && *value != "CANCELLED" && *value != "NEEDS-ACTION"
            && *value != "COMPLETED" && *value != "IN-PROCESS") {
        throw ParserException(value.pos(), "Invalid " + NAME + " property value!");
    }
    Status status;
    status.value = std::move(core::ValueParser::parseText(
                                  value.pos(), value->begin(), value->end()));
    return status;
}

} // namespace properties
} // namespace ical

