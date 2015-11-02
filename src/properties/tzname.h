#ifndef ICAL_PROPERTIES_TZNAME_H
#define ICAL_PROPERTIES_TZNAME_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZName
{
public:
    TZName() {}

    void print(std::ostream & out);

    static TZName parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZNAME_H

