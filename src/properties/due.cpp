#include "due.h"

namespace ical {
namespace properties {

const std::string Due::NAME = "DUE";

void Due::print(std::ostream &out) const{

}

Due Due::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

