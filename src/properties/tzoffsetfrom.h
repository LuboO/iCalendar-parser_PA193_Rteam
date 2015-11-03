#ifndef ICAL_PROPERTIES_TZOFFSETFROM_H
#define ICAL_PROPERTIES_TZOFFSETFROM_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZOffsetFrom
{
public:
    TZOffsetFrom() {}

    void print(std::ostream &out) const;

    static TZOffsetFrom parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETFROM_H

