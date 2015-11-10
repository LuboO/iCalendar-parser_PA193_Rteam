#ifndef ICAL_PROPERTIES_trigger_H
#define ICAL_PROPERTIES_trigger_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "data/datetime.h"
#include "data/duration.h"

#include "parameters/related.h"

namespace ical {
namespace properties {

class Trigger
{
private:
    bool absolute;

    data::Duration duration;
    parameters::Related relation;

    data::DateTime start;

    /*
     * NOTE: RFC states that this property can also have the TZID parameter,
     * however it is not mentioned in the ABNF grammar, so we do not allow it
     */

public:
    static const std::string NAME;

    bool isAbsolute() const noexcept { return absolute; }

    const data::Duration &getDuration() const
    {
        if (absolute) {
            throw std::logic_error("The trigger is absolute!");
        }
        return duration;
    }
    const parameters::Related &getRelation() const
    {
        if (absolute) {
            throw std::logic_error("The trigger is absolute!");
        }
        return relation;
    }

    const data::DateTime &getStart() const
    {
        if (!absolute) {
            throw std::logic_error("The trigger is relative!");
        }
        return start;
    }

    Trigger(data::Duration &&duration, parameters::Related &&relation)
        : absolute(false), duration(std::move(duration)), relation(relation), start()
    {
    }
    explicit Trigger(data::DateTime &&start)
        : absolute(true), duration(), relation(), start(std::move(start))
    {
    }

    void print(std::ostream &out) const;

    static Trigger parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_trigger_H

