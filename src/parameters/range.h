#ifndef ICAL_PARAMETERS_RANGE_H
#define ICAL_PARAMETERS_RANGE_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Range
{
public:
    Range() {}

    void print(std::ostream & out);

    static Range parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_RANGE_H

