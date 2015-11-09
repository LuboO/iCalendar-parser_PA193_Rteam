#include "transp.h"

namespace ical {
namespace properties {

const std::string Transp::NAME = "TRANSP";

void Transp::print(std::ostream &out) const{

}

Transp Transp::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

