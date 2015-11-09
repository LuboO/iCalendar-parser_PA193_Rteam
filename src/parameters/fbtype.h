#ifndef ICAL_PARAMETERS_FBTYPE_H
#define ICAL_PARAMETERS_FBTYPE_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class FBType
{
private:
    std::string value;
public:
    static const std::string NAME;

    FBType() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static FBType parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_FBTYPE_H

