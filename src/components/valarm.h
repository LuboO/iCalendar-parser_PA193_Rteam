#ifndef ICAL_COMPONENTS_ALARM_H
#define ICAL_COMPONENTS_ALARM_H

#include "core/genericcomponent.h"

#include <ostream>
#include <vector>

#include "properties/action.h"
#include "properties/trigger.h"
#include "properties/durationprop.h"
#include "properties/repeat.h"
#include "properties/attach.h"
#include "properties/description.h"
#include "properties/summary.h"
#include "properties/attendee.h"

namespace ical {
namespace components {

class VAlarm
{
private:
    /** EVENT component properties **/
    std::vector<properties::Action> actionProp;
    std::vector<properties::Trigger> triggerProp;
    std::vector<properties::DurationProp> durationProp;
    std::vector<properties::Repeat> repeatProp;
    std::vector<properties::Attach> attachProp;
    std::vector<properties::Description> descriptionProp;
    std::vector<properties::Summary> summaryProp;
    std::vector<properties::Attendee> attendeeProp;
public:
    static const std::string NAME;

    VAlarm() {}

    void print(std::ostream &out) const;

    static VAlarm parse(const core::WithPos<core::GenericComponent> &generic);
    const std::vector<properties::Action> getActionProp() const noexcept{return actionProp;}
    const std::vector<properties::Trigger> getTriggerProp() const noexcept{return triggerProp;}
    const std::vector<properties::DurationProp> getDurationProp() const noexcept{return durationProp;}
    const std::vector<properties::Repeat> getRepeatProp() const noexcept{return repeatProp;}
    const std::vector<properties::Attach> getAttachProp() const noexcept{return attachProp;}
    const std::vector<properties::Description> getDescriptionProp() const noexcept{return descriptionProp;}
    const std::vector<properties::Summary> getSummaryProp() const noexcept{return summaryProp;}
    const std::vector<properties::Attendee> getAttendeeProp() const noexcept{return attendeeProp;}
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_ALARM_H
