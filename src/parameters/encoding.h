#ifndef ICAL_PARAMETERS_ENCODING_H
#define ICAL_PARAMETERS_ENCODING_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Encoding
{
public:
    Encoding() {}

    void print(std::ostream & out);

    static Encoding parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_ENCODING_H
