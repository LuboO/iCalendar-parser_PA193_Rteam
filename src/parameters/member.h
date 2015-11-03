#ifndef ICAL_PARAMETERS_MEMBER_H
#define ICAL_PARAMETERS_MEMBER_H

#include <ostream>
#include <vector>
#include <regex>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Member
{
private:
    std::string value;
public:
    Member() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out);

    static Member parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_MEMBER_H

