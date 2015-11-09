#ifndef ICAL_PROPERTIES_TZOFFSETFROM_H
#define ICAL_PROPERTIES_TZOFFSETFROM_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"
#include "data/utcoffset.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

class TZOffsetFrom
{
private:
    data::UTCOffset value;
public:
    static const std::string NAME;

    TZOffsetFrom() {}

    const data::UTCOffset &getValue() const noexcept { return value; }

    void print(std::ostream & out) const;

    static TZOffsetFrom parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETFROM_H

