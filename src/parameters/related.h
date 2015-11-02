#ifndef ICAL_PARAMETERS_RELATED_H
#define ICAL_PARAMETERS_RELATED_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Related
{
public:
    Related() {}

    void print(std::ostream & out);

    static Related parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_RELATED_H

