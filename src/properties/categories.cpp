#include "categories.h"

namespace ical {
namespace properties {

const std::string Categories::NAME = "CATEGORIES";

void Categories::print(std::ostream &out) const {

}

Categories Categories::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

