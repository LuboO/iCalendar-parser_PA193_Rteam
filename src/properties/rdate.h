#ifndef ICAL_PROPERTIES_rdate_H
#define ICAL_PROPERTIES_rdate_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class RDate
{
private:
    // TODO

public:
    RDate() {}

    void print(std::ostream &out) const;

    static RDate parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_rdate_H

