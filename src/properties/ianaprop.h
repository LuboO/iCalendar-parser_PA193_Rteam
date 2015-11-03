#ifndef ICAL_PROPERTIES_IANAPROP_H
#define ICAL_PROPERTIES_IANAPROP_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class IanaProp
{
public:
    IanaProp() {}

    void print(std::ostream & out);

    static IanaProp parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_IANAPROP_H

