#ifndef ICAL_PARAMETERS_FMTTYPE_H
#define ICAL_PARAMETERS_FMTTYPE_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class FmtType
{
public:
    FmtType() {}

    void print(std::ostream & out);

    static FmtType parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_FMTTYPE_H

