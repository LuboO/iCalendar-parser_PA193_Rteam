#ifndef ICAL_PROPERTIES_rrule_H
#define ICAL_PROPERTIES_rrule_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class RRule
{
private:
    // TODO

public:
    RRule() {}

    void print(std::ostream &out) const;

    static RRule parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_rrule_H

