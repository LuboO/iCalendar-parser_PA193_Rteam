#ifndef ICAL_PROPERTIES_TZURL_H
#define ICAL_PROPERTIES_TZURL_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class TZUrl
{
private:
    std::string value;
public:
    TZUrl() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static TZUrl parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZURL_H

