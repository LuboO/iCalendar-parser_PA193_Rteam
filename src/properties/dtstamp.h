#ifndef ICAL_PROPERTIES_dtstamp_H
#define ICAL_PROPERTIES_dtstamp_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class DTStamp
{
private:
    // TODO

public:
    DTStamp() {}

    void print(std::ostream &out) const;

    static DTStamp parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_dtstamp_H

