#ifndef ICAL_PROPERTIES_TZOFFSETTO_H
#define ICAL_PROPERTIES_TZOFFSETTO_H

#include <ostream>
#include <vector>

#include "parserexception.h"
#include "core/genericproperty.h"
#include "data/utcoffset.h"

namespace ical {
namespace properties {

class TZOffsetTo
{
private:
    data::UTCOffset value;
public:
    TZOffsetTo() {}

    const data::UTCOffset &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static TZOffsetTo parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETTO_H

