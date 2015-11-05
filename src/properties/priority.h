#ifndef ICAL_PROPERTIES_PRIORITY_H
#define ICAL_PROPERTIES_PRIORITY_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Priority
{
public:
    Priority() {}

    void print(std::ostream & out) const;

    static Priority parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_PRIORITY_H

