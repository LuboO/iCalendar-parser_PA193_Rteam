#ifndef ICAL_PARAMETERS_calusertype_H
#define ICAL_PARAMETERS_calusertype_H

#include <ostream>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class CalUserType
{
private:
    std::string value;

public:
    const std::string &getValue() const noexcept { return value; }

    CalUserType() {}

    void print(std::ostream &out) const;

    static CalUserType parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_calusertype_H

