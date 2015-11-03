#ifndef TZID_PARAM_H
#define TZID_PARAM_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Tzid_param
{
    std::string value;
public:
    Tzid_param() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out);

    static Tzid_param parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // TZID_PARAM_H
