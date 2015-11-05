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
public:
    Geo() {}

    void print(std::ostream & out) const;

    static Geo parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_GEO_H

