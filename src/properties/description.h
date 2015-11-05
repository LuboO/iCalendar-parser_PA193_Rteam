#ifndef ICAL_PROPERTIES_DESCRIPTION_H
#define ICAL_PROPERTIES_DESCRIPTION_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Description
{
public:
    Description() {}

    void print(std::ostream & out) const;

    static Description parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DESCRIPTION_H

