#ifndef ICAL_CORE_GENERICPROPERTY_H
#define ICAL_CORE_GENERICPROPERTY_H

#include "core/genericpropertyparameter.h"

#include <vector>

namespace ical {
namespace core {

class GenericProperty
{
private:
    WithPos<std::string> name;
    WithPos<std::string> value;
    std::vector<WithPos<GenericPropertyParameter>> params;

public:
    const WithPos<std::string> &getName() const noexcept { return name; }
    const WithPos<std::string> &getValue() const noexcept { return value; }
    const std::vector<WithPos<GenericPropertyParameter>> &getParameters() const noexcept
    {
        return params;
    }

    GenericProperty(const WithPos<std::string> &name,
                    const WithPos<std::string> &value,
                    const std::vector<WithPos<GenericPropertyParameter>> &params)
        : name(name), value(value), params(params)
    {
    }

    GenericProperty(WithPos<std::string> &&name,
                    WithPos<std::string> &&value,
                    std::vector<WithPos<GenericPropertyParameter>> &&params)
        : name(std::move(name)), value(std::move(value)),
          params(std::move(params))
    {
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_GENERICPROPERTY_H
