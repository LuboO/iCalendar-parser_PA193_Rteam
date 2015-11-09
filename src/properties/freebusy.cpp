#include "freebusy.h"

namespace ical {
namespace properties {

const std::string FREEBUSY::NAME = "FREEBUSY";

void FREEBUSY::print(std::ostream &out) const{

}

FREEBUSY FREEBUSY::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

