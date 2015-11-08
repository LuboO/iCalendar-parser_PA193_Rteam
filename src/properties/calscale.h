#ifndef ICAL_PROPERTIES_CALSCALE_H
#define ICAL_PROPERTIES_CALSCALE_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class CalScale
{
private:
    std::string value;
public:
    CalScale() {}

    void print(std::ostream & out) const;

    static CalScale parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_CALSCALE_H

