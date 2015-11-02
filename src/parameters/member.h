#ifndef ICAL_PARAMETERS_MEMBER_H
#define ICAL_PARAMETERS_MEMBER_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Member
{
public:
    Member() {}

    void print(std::ostream & out);

    static Member parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_MEMBER_H

