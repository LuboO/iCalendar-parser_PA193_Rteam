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
public:
    TZUrl() {}

    void print(std::ostream & out);

    static TZUrl parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZURL_H

