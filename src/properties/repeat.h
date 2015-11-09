#ifndef ICAL_PROPERTIES_repeat_H
#define ICAL_PROPERTIES_repeat_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Repeat
{
private:
    int count;

public:
    static const std::string NAME;

    int getValue() const noexcept { return count; }

    Repeat() : count(0)
    {
    }
    Repeat(int count) : count(count)
    {
    }

    void print(std::ostream &out) const;

    static Repeat parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_repeat_H

