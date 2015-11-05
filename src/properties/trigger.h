#ifndef ICAL_PROPERTIES_trigger_H
#define ICAL_PROPERTIES_trigger_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Trigger
{
private:
    // TODO

public:
    Trigger() {}

    void print(std::ostream &out) const;

    static Trigger parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_trigger_H

