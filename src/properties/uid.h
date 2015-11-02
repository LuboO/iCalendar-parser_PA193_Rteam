#ifndef ICAL_PROPERTIES_UID_H
#define ICAL_PROPERTIES_UID_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Uid
{
public:
    Uid() {}

    void print(std::ostream & out);

    static Uid parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_UID_H

