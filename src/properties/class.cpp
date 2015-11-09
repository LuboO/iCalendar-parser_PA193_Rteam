#include "class.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Class::NAME = "CLASS";

void Class::print(std::ostream &out) const {
    out << "CLASS:" << value << "\r\n";
}

Class Class::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The CLASS property must have no parameters!");
    }

    auto &value = generic->getValue();
    if (*value != "PUBLIC" && *value != "PRIVATE"
            && *value != "CONFIDENTIAL") {
        throw ParserException(value.pos(), "Invalid CLASS property value!");
    }
    Class clas;
    clas.value = std::move(core::ValueParser::parseText(
                                  value.pos(), value->begin(), value->end()));
    return clas;
}

} // namespace properties
} // namespace ical

