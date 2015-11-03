#ifndef ICAL_PARAMETERS_PARTSTAT_H
#define ICAL_PARAMETERS_PARTSTAT_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class PartStat
{
private:
    std::string value;
public:
    PartStat() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out);

    static PartStat parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_PARTSTAT_H

