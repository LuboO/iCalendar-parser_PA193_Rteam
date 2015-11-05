#ifndef ICAL_PROPERTIES_PERCENTCOMPLETE_H
#define ICAL_PROPERTIES_PERCENTCOMPLETE_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class PercentComplete
{
public:
    PercentComplete() {}

    void print(std::ostream & out) const;

    static PercentComplete parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_PERCENTCOMPLETE_H
