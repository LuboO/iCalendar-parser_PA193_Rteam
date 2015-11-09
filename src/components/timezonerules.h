#ifndef ICAL_COMPONENTS_TIMEZONERULES_H
#define ICAL_COMPONENTS_TIMEZONERULES_H

#include "core/genericcomponent.h"

#include "properties/dtstart.h"
#include "properties/tzoffsetfrom.h"
#include "properties/tzoffsetto.h"
#include "properties/rrule.h"
#include "properties/comment.h"
#include "properties/rdate.h"
#include "properties/tzname.h"

namespace ical {
namespace components {

class TimeZoneRules
{
private:
    properties::DTStart start;
    properties::TZOffsetFrom from;
    properties::TZOffsetTo to;

    std::vector<properties::RRule> rrules;

    std::vector<properties::Comment> comments;
    std::vector<properties::RDate> rdates;
    std::vector<properties::TZName> names;

public:
    const properties::DTStart &getStart() const noexcept { return start; }
    const properties::TZOffsetFrom &getOffsetFrom() const noexcept { return from; }
    const properties::TZOffsetTo &getOffsetTo() const noexcept { return to; }

    const std::vector<properties::RRule> &getReccurenceRules() const noexcept
    {
        return rrules;
    }

    const std::vector<properties::RDate> &getOnsetDates() const noexcept
    {
        return rdates;
    }

    const std::vector<properties::TZName> &getNames() const noexcept
    {
        return names;
    }

    const std::vector<properties::Comment> &getComments() const noexcept
    {
        return comments;
    }

    TimeZoneRules() : rrules(), comments(), rdates(), names() { }

    void print(std::ostream &out, const char *name) const;

    static TimeZoneRules parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_TIMEZONERULES_H
