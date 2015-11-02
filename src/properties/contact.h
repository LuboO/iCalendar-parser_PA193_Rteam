#ifndef ICAL_PROPERTIES_CONTACT_H
#define ICAL_PROPERTIES_CONTACT_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Contact
{
public:
    Contact() {}

    void print(std::ostream & out);

    static Contact parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_CONTACT_H

