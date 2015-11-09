#include "resources.h"

namespace ical {
namespace properties {

const std::string Resources::NAME = "RESOURCES";

void Resources::print(std::ostream &out) const {

}

Resources Resources::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

