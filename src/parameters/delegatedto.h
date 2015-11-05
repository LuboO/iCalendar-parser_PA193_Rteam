#ifndef ICAL_PARAMETERS_delegatedto_H
#define ICAL_PARAMETERS_delegatedto_H

#include <ostream>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class DelegatedTo
{
private:
    // TODO

public:
    DelegatedTo() {}

    void print(std::ostream &out) const;

    static DelegatedTo parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_delegatedto_H

