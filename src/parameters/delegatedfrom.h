#ifndef ICAL_PARAMETERS_delegatedfrom_H
#define ICAL_PARAMETERS_delegatedfrom_H

#include <ostream>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class DelegatedFrom
{
private:
    // TODO

public:
    DelegatedFrom() {}

    void print(std::ostream &out) const;

    static DelegatedFrom parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_delegatedfrom_H

