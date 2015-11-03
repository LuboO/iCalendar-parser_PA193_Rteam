#include "attendee.h"

namespace ical {
namespace properties {

void Attendee::print(std::ostream &out) const {

}

Attendee Attendee::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

