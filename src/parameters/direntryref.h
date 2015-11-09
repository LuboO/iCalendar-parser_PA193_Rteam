#ifndef ICAL_PARAMETERS_direntryref_H
#define ICAL_PARAMETERS_direntryref_H

#include <ostream>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class DirEntryRef
{
private:
    std::string value;

public:
    static const std::string NAME;

    const std::string &getValue() const noexcept { return value; }

    DirEntryRef() {}

    void print(std::ostream &out) const;

    static DirEntryRef parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_direntryref_H

