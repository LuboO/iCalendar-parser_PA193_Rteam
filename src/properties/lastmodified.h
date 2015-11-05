#ifndef ICAL_PROPERTIES_lastmodified_H
#define ICAL_PROPERTIES_lastmodified_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class LastModified
{
private:
    // TODO

public:
    LastModified() {}

    void print(std::ostream &out) const;

    static LastModified parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_lastmodified_H

