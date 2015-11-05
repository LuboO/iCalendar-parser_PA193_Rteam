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
    // TODO

public:
    CalUserType() {}

    void print(std::ostream &out) const;

    static CalUserType parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_calusertype_H

