#ifndef ICAL_PROPERTIES_ATTENDEE_H
#define ICAL_PROPERTIES_ATTENDEE_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Attendee
{
public:
    Attendee() {}

    void print(std::ostream & out);

    static Attendee parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ATTENDEE_H

