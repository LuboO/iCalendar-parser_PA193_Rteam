#ifndef ICAL_PROPERTIES_TZOFFSETTO_H
#define ICAL_PROPERTIES_TZOFFSETTO_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZOffsetTo
{
public:
    TZOffsetTo() {}

    void print(std::ostream & out);

    static TZOffsetTo parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETTO_H

