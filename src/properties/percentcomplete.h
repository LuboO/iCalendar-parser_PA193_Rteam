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
private:
    int value;
public:
    static const std::string NAME;

    PercentComplete() {}

    void print(std::ostream & out) const;

    static PercentComplete parse(const core::WithPos<core::GenericProperty> &generic);

    int getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_PERCENTCOMPLETE_H

