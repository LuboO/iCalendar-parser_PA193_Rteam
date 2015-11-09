#include "completed.h"
#include "core/valueparser.h"


namespace ical {
namespace properties {

void Completed::print(std::ostream &out) const{
    out << "COMPLETED:";
    value.print(out);
    out << "\r\n";

}

Completed Completed::parse(const core::WithPos<core::GenericProperty> &generic) {
    auto &value = generic->getValue();
    Completed completed;
    completed.value = std::move(core::ValueParser::parseDateTime(value.pos(), value->begin(), value->end()));
    return completed;
}

} // namespace properties
} // namespace ical

