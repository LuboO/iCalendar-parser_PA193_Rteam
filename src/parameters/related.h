#ifndef ICAL_PARAMETERS_RELATED_H
#define ICAL_PARAMETERS_RELATED_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Related
{
private:
    std::string value;
public:
    Related() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out);

    static Related parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_RELATED_H

