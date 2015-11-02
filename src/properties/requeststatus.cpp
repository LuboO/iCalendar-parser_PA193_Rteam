#include "requeststatus.h"

namespace ical {
namespace properties {

void RequestStatus::print(std::ostream &out) {

}

RequestStatus RequestStatus::parse(const core::WithPos<core::GenericComponent> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

