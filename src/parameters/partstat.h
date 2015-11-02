#ifndef ICAL_PARAMETERS_PARTSTAT_H
#define ICAL_PARAMETERS_PARTSTAT_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class PartStat
{
public:
    PartStat() {}

    void print(std::ostream & out);

    static PartStat parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_PARTSTAT_H

