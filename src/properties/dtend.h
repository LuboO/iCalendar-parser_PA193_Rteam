#ifndef ICAL_PROPERTIES_DTEND_H
#define ICAL_PROPERTIES_DTEND_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class DTEnd
{
public:
    static const std::string NAME;

    DTEnd() {}

    void print(std::ostream & out) const;

    static DTEnd parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DTEND_H

