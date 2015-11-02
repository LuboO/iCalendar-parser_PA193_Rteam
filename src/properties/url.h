#ifndef ICAL_PROPERTIES_URL_H
#define ICAL_PROPERTIES_URL_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Url
{
public:
    Url() {}

    void print(std::ostream & out);

    static Url parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_URL_H

