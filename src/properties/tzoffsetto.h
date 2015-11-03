#ifndef ICAL_PROPERTIES_TZOFFSETTO_H
#define ICAL_PROPERTIES_TZOFFSETTO_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZOffsetTo
{
public:
    TZOffsetTo() {}

    void print(std::ostream &out) const;

    static TZOffsetTo parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETTO_H

