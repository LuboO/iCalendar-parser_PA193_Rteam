#ifndef ICAL_PROPERTIES_NONSTDPROP_H
#define ICAL_PROPERTIES_NONSTDPROP_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class NonStdProp
{
public:
    NonStdProp() {}

    void print(std::ostream & out);

    static NonStdProp parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_NONSTDPROP_H

