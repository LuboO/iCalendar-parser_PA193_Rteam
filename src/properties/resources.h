#ifndef ICAL_PROPERTIES_RESOURCES_H
#define ICAL_PROPERTIES_RESOURCES_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Resources
{
public:
    Resources() {}

    void print(std::ostream & out) const;

    static Resources parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RESOURCES_H

