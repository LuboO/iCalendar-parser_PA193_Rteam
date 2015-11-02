#include "nonstdprop.h"

namespace ical {
namespace properties {

void NonStdProp::print(std::ostream &out) {

}

NonStdProp NonStdProp::parse(const core::WithPos<core::GenericComponent> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

