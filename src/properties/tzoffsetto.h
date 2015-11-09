#ifndef ICAL_PROPERTIES_TZOFFSETTO_H
#define ICAL_PROPERTIES_TZOFFSETTO_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"
#include "data/utcoffset.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

class TZOffsetTo
{
private:
    data::UTCOffset value;
public:
    static const std::string NAME;

    TZOffsetTo() {}

    const data::UTCOffset &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static TZOffsetTo parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZOFFSETTO_H

