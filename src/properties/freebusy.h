#ifndef ICAL_PROPERTIES_FREEBUSY_H
#define ICAL_PROPERTIES_FREEBUSY_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class FREEBUSY
{
public:
    static const std::string NAME;

    FREEBUSY() {}

    void print(std::ostream & out) const;

    static FREEBUSY parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_FREEBUSY_H

