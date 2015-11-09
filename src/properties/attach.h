#ifndef ICAL_PROPERTIES_ATTACH_H
#define ICAL_PROPERTIES_ATTACH_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Attach
{
public:
    static const std::string NAME;

    Attach() {}

    void print(std::ostream & out) const;

    static Attach parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ATTACH_H

