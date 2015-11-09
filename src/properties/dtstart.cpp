#include "dtstart.h"

namespace ical {
namespace properties {

const std::string DTStart::NAME = "DTSTART";

void DTStart::print(std::ostream &out) const{

}

DTStart DTStart::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

