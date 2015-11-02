#ifndef ICAL_PROPERTIES_REQUESTSTATUS_H
#define ICAL_PROPERTIES_REQUESTSTATUS_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class RequestStatus
{
public:
    RequestStatus() {}

    void print(std::ostream & out);

    static RequestStatus parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_REQUESTSTATUS_H

