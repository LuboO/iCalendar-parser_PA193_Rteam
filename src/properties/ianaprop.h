#ifndef ICAL_PROPERTIES_IANAPROP_H
#define ICAL_PROPERTIES_IANAPROP_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class IanaProp
{
public:
    IanaProp() {}

    void print(std::ostream & out);

    static IanaProp parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_IANAPROP_H

