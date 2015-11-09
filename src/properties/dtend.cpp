#include "dtend.h"

namespace ical {
namespace properties {

const std::string DTEnd::NAME = "DTEND";

void DTEnd::print(std::ostream &out) const{

}

DTEnd DTEnd::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

