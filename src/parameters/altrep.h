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
    std::string value;

public:
    static const std::string NAME;

    const std::string &getValue() const noexcept { return value; }

    AltRep() {}

    void print(std::ostream &out) const;

    static AltRep parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_altrep_H

