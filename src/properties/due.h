#ifndef ICAL_PROPERTIES_DUE_H
#define ICAL_PROPERTIES_DUE_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Due
{
public:
    static const std::string NAME;

    Due() {}

    void print(std::ostream & out) const;

    static Due parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DUE_H

