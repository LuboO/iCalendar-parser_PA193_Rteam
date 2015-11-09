#include "class.h"

namespace ical {
namespace properties {

const std::string Class::NAME = "CLASS";

void Class::print(std::ostream &out) const {

}

Class Class::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

