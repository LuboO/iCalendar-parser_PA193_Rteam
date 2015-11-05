#ifndef ICAL_PROPERTIES_DTEND_H
#define ICAL_PROPERTIES_DTEND_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class DTEND
{
public:
    DTEND() {}

    void print(std::ostream & out) const;

    static DTEND parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DTEND_H

