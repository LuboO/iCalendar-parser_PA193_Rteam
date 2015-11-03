#ifndef ICAL_PROPERTIES_ORGANIZER_H
#define ICAL_PROPERTIES_ORGANIZER_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Organizer
{
public:
    Organizer() {}

    void print(std::ostream &out) const;

    static Organizer parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ORGANIZER_H

