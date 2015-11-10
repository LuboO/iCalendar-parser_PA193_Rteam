#ifndef ICAL_PROPERTIES_GEO_H
#define ICAL_PROPERTIES_GEO_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Geo
{
private:
    double latitude;
    double longitude;

public:
    static const std::string NAME;

    Geo(double latitude, double longitude)
        : latitude(latitude), longitude(longitude)
    {
    }

    void print(std::ostream & out) const;

    static Geo parse(const core::WithPos<core::GenericProperty> &generic);

    double getlatitude() const noexcept { return latitude; }
    double getlongitude() const noexcept { return longitude; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_GEO_H

