#include "geo.h"

namespace ical {
namespace properties {

const std::string Geo::NAME = "GEO";

void Geo::print(std::ostream &out) const {

}

Geo Geo::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

