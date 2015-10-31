#ifndef ICAL_CORE_GENERICPROPERTYPARAMETER_H
#define ICAL_CORE_GENERICPROPERTYPARAMETER_H

#include "withpos.h"

#include <string>

namespace ical {
namespace core {

class GenericPropertyParameter
{
private:
    WithPos<std::string> name;
    WithPos<std::string> value;

public:
    const WithPos<std::string> &getName() const noexcept { return name; }
    const WithPos<std::string> &getValue() const noexcept { return value; }

    GenericPropertyParameter(const WithPos<std::string> &name,
                             const WithPos<std::string> &value)
        : name(name), value(value)
    {
    }

    GenericPropertyParameter(WithPos<std::string> &&name,
                             WithPos<std::string> &&value)
        : name(std::move(name)), value(std::move(value))
    {
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_GENERICPROPERTYPARAMETER_H
