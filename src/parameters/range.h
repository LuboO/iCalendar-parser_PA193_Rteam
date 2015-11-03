#ifndef ICAL_PARAMETERS_RANGE_H
#define ICAL_PARAMETERS_RANGE_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Range
{
    std::string value;
public:
    Range() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static Range parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_RANGE_H

