#ifndef ICAL_PROPERTIES_TZID_H
#define ICAL_PROPERTIES_TZID_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZId
{
private:
    std::string value;
public:
    TZId() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out);

    static TZId parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZID_H

