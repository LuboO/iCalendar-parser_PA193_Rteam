#ifndef ICAL_PROPERTIES_TZOFFSETFROM_H
#define ICAL_PROPERTIES_TZOFFSETFROM_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZOffsetFrom
{
public:
    TZOffsetFrom() {}

    void print(std::ostream & out);

    static TZOffsetFrom parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETFROM_H

