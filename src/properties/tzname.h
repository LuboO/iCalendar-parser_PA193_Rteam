#ifndef ICAL_PROPERTIES_TZNAME_H
#define ICAL_PROPERTIES_TZNAME_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZName
{
public:
    TZName() {}

    void print(std::ostream &out) const;

    static TZName parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZNAME_H

