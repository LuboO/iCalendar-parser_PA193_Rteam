#ifndef ICAL_PROPERTIES_CLASS_H
#define ICAL_PROPERTIES_CLASS_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Class
{
public:
    Class() {}

    void print(std::ostream & out) const;

    static Class parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_CLASS_H

