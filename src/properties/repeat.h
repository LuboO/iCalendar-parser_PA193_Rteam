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
    // TODO

public:
    Repeat() {}

    void print(std::ostream &out) const;

    static Repeat parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_repeat_H

