#ifndef ICAL_PROPERTIES_exdate_H
#define ICAL_PROPERTIES_exdate_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class ExDate
{
private:
    // TODO

public:
    ExDate() {}

    void print(std::ostream &out) const;

    static ExDate parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_exdate_H

