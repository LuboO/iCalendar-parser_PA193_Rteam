#include "vevent.h"

namespace ical {
namespace components {

using namespace ical::core;

void VEvent::print(std::ostream &out) const {

}

VEvent VEvent::parse(const core::WithPos<core::GenericComponent> &generic) {
    VEvent event;

    const std::vector<WithPos<GenericComponent>> & comps =
            generic.value().getSubcomponents();
    for(const WithPos<GenericComponent> & i : comps) {
        if(i.value().getName().value() == "VALARM") {
            VAlarm alarm = VAlarm::parse(i);
            event.alarmComp.push_back(alarm);
        } else {
            throw ParserException(i.pos() , "VEVENT component can't contain other component"
                                            "than VALARM");
        }
    }
    return event;
}

} // namespace components
} // namespace ical

