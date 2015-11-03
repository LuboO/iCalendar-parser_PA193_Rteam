#ifndef ICAL_PROPERTIES_UID_H
#define ICAL_PROPERTIES_UID_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Uid
{
public:
    Uid() {}

    void print(std::ostream &out) const;

    static Uid parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_UID_H

