#ifndef ROLE_H
#define ROLE_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {
class Role
{
private:
    std::string value;
public:
    Role() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out) const;

    static Role parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};
}// namespace parameters
} // namespace ical



#endif // ROLE_H
