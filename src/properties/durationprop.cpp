#include "durationprop.h"

namespace ical {
namespace properties {

const std::string DurationProp::NAME = "DURATION";

void DurationProp::print(std::ostream &out) const{

}

DurationProp DurationProp::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

