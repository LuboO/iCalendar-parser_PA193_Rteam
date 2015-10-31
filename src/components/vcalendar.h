#ifndef ICAL_COMPONENTS_VCALENDAR_H
#define ICAL_COMPONENTS_VCALENDAR_H

#include "core/genericcomponent.h"

#include <ostream>

namespace ical {
namespace components {

class VCalendar
{
private:
    /* TODO ... */

public:
    VCalendar(/* TODO ... */)
    {
    }

    void print(std::ostream &out);

    static VCalendar parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VCALENDAR_H
