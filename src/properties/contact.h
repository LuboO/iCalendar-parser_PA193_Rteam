#ifndef ICAL_PARAMETERS_CONTACT_H
#define ICAL_PARAMETERS_CONTACT_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Contact
{
public:
    Contact() {}

    void print(std::ostream & out);

    static Contact parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_CONTACT_H

