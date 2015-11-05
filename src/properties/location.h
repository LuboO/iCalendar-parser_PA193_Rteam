#ifndef ICAL_PROPERTIES_LOCATION_H
#define ICAL_PROPERTIES_LOCATION_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Location
{
public:
    Location() {}

    void print(std::ostream & out) const;

    static Location parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_LOCATION_H

