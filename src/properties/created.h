#ifndef ICAL_PROPERTIES_created_H
#define ICAL_PROPERTIES_created_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Created
{
private:
    // TODO

public:
    Created() {}

    void print(std::ostream &out) const;

    static Created parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_created_H

