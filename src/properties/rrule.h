#ifndef ICAL_PROPERTIES_rrule_H
#define ICAL_PROPERTIES_rrule_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "data/recurrencerule.h"

namespace ical {
namespace properties {

class RRule
{
private:
    data::RecurrenceRule value;

public:
    const data::RecurrenceRule &getValue() const noexcept
    {
        return value;
    }

    RRule(data::RecurrenceRule &&value) : value(std::move(value))
    {
    }

    void print(std::ostream &out) const;

    static RRule parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_rrule_H

