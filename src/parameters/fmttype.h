#ifndef ICAL_PARAMETERS_FMTTYPE_H
#define ICAL_PARAMETERS_FMTTYPE_H

#include <ostream>
#include <vector>
#include <string>
#include <regex>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class FmtType
{
private:
    std::string value;
public:
    FmtType() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static FmtType parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_FMTTYPE_H

