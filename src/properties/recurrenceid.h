#ifndef ICAL_PROPERTIES_RECURRENCEID_H
#define ICAL_PROPERTIES_RECURRENCEID_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class RecurrenceId
{
public:
    RecurrenceId() {}

    void print(std::ostream &out) const;

    static RecurrenceId parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RECURRENCEID_H

