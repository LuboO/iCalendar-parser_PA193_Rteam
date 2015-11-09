#include "completed.h"

namespace ical {
namespace properties {

const std::string Completed::NAME = "COMPLETED";

void Completed::print(std::ostream &out) const{

}

Completed Completed::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

