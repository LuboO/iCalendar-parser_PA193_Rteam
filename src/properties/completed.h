#ifndef ICAL_PROPERTIES_COMPLETED_H
#define ICAL_PROPERTIES_COMPLETED_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Completed
{
public:
    static const std::string NAME;

    Completed() {}

    void print(std::ostream & out) const;

    static Completed parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_COMPLETED_H

