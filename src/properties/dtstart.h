#ifndef ICAL_PROPERTIES_DTSTART_H
#define ICAL_PROPERTIES_DTSTART_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class DTStart
{
public:
    static const std::string NAME;

    DTStart() {}

    void print(std::ostream & out) const;

    static DTStart parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DTSTART_H

