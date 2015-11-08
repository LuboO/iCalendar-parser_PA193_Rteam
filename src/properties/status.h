#ifndef ICAL_PROPERTIES_STATUS_H
#define ICAL_PROPERTIES_STATUS_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Status
{
private:
    std::string value;
public:
    Status() {}

    void print(std::ostream & out) const;

    static Status parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_STATUS_H

