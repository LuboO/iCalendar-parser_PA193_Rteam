#ifndef ICAL_CORE_GENERICCOMPONENT_H
#define ICAL_CORE_GENERICCOMPONENT_H

#include "core/genericproperty.h"

namespace ical {
namespace core {

class GenericComponent
{
private:
    WithPos<std::string> name;
    std::vector<WithPos<GenericProperty>> properties;
    std::vector<WithPos<GenericComponent>> subcomponents;

public:
    const WithPos<std::string> &getName() const noexcept { return name; }
    const std::vector<WithPos<GenericProperty>> &getProperties() const noexcept
    {
        return properties;
    }
    const std::vector<WithPos<GenericComponent>> &getSubcomponents() const noexcept
    {
        return subcomponents;
    }

    GenericComponent(const WithPos<std::string> &name,
                     const std::vector<WithPos<GenericProperty>> &properties,
                     const std::vector<WithPos<GenericComponent>> &subcomponents)
         : name(name), properties(properties), subcomponents(subcomponents)
    {
    }

    GenericComponent(WithPos<std::string> &&name,
                     std::vector<WithPos<GenericProperty>> &&properties,
                     std::vector<WithPos<GenericComponent>> &&subcomponents)
         : name(std::move(name)), properties(std::move(properties)),
           subcomponents(std::move(subcomponents))
    {
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_GENERICCOMPONENT_H
