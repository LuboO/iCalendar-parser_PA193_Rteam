#include "durationprop.h"

namespace ical {
namespace properties {

const std::string DurationProp::NAME = "DURATION";

void DurationProp::print(std::ostream &out) const{
    out << "DURATION";
    out << ":" ;
    value.print(out);
    out << "\r\n";
}

DurationProp DurationProp::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The DURATION property must have no parameters!");
    }

    auto &value = generic->getValue();
    DurationProp duration;
    duration.value = std::move(data::Duration::parse(value.pos(), value->begin(), value->end()));
    return duration;
}

} // namespace properties
} // namespace ical

