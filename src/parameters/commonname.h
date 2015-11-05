#ifndef ICAL_PARAMETERS_commonname_H
#define ICAL_PARAMETERS_commonname_H

#include <ostream>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class CommonName
{
private:
    std::string value;

public:
    const std::string &getValue() const noexcept { return value; }

    CommonName() {}

    void print(std::ostream &out) const;

    static CommonName parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_commonname_H

