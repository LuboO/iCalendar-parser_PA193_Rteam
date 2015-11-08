#ifndef ICAL_PROPERTIES_VERSION_H
#define ICAL_PROPERTIES_VERSION_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Version
{
private:
    std::string value;
public:
    Version() {}

    void print(std::ostream & out) const;

    static Version parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_VERSION_H

