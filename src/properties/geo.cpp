#include "geo.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

void Geo::print(std::ostream &out) const {
    out << "GEO:" << latitude << ":" << longitude << "\r\n";
}

Geo Geo::parse(const core::WithPos<core::GenericProperty> &generic) {    
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The GEO property must have no parameters!");
    }

    auto &value = generic->getValue();
    Geo geo;



    std::vector<double> values = std::move(core::ValueParser::parseDelimited(
                                              value.pos(), value->begin(), value->end(),
                                              core::ValueParser::parseFloat, ':'));

    if (values.size()!=2) throw ParserException(generic.pos(), "The GEO property must have exactly two float property values!");
    geo.latitude = values[0];
    geo.longitude = values[1];

    return geo;
}

} // namespace properties
} // namespace ical

