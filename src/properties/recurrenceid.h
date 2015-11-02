#ifndef ICAL_PROPERTIES_RECURRENCEID_H
#define ICAL_PROPERTIES_RECURRENCEID_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class RecurrenceId
{
public:
    RecurrenceId() {}

    void print(std::ostream & out);

    static RecurrenceId parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RECURRENCEID_H

