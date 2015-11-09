#ifndef ICAL_PROPERTIES_CLASS_H
#define ICAL_PROPERTIES_CLASS_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Class
{
private:
    std::string value;
public:
    Class() {}

    void print(std::ostream & out) const;

    static Class parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_CLASS_H

