#ifndef ICAL_COMPONENTS_VEVENT_H
#define ICAL_COMPONENTS_VEVENT_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

/* Properties */
#include "properties/dtstamp.h"
#include "properties/uid.h"
//#include "properties/class.h"
#include "properties/created.h"
//#include "properties/description.h"
//#include "properties/geo.h"
#include "properties/lastmodified.h"
//#include "properties/location.h"
#include "properties/organizer.h"
//#include "properties/priority.h"
#include "properties/sequence.h"
//#include "properties/status.h"
//#include "properties/summary.h"
//#include "properties/transp.h"
#include "properties/url.h"
#include "properties/recurrenceid.h"

/* Components */
#include "components/valarm.h"

namespace ical {
namespace components {

class VEvent
{
private:
    /* EVENT component properties */
    /* EVENT component components */
    std::vector<ical::components::VAlarm> alarmComp;

public:
    VEvent() {}

    void print(std::ostream &out) const;

    static VEvent parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VEVENT_H
