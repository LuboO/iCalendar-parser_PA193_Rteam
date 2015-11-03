#ifndef ICAL_PROPERTIES_ATTENDEE_H
#define ICAL_PROPERTIES_ATTENDEE_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Attendee
{
public:
    Attendee() {}

    void print(std::ostream &out) const;

    static Attendee parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ATTENDEE_H

