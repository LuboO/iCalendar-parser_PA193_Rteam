#ifndef ICAL_PARAMETERS_FBTYPE_H
#define ICAL_PARAMETERS_FBTYPE_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class FBType
{
public:
    FBType() {}

    void print(std::ostream & out);

    static FBType parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_FBTYPE_H

