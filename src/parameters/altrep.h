#ifndef ICAL_PARAMETERS_altrep_H
#define ICAL_PARAMETERS_altrep_H

#include <ostream>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class AltRep
{
private:
    // TODO

public:
    AltRep() {}

    void print(std::ostream &out) const;

    static AltRep parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_altrep_H

