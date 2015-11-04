#ifndef ICAL_CORE_GENERICPROPERTYPARAMETER_H
#define ICAL_CORE_GENERICPROPERTYPARAMETER_H

#include "withpos.h"
#include "parserexception.h"

#include <string>
#include <vector>

namespace ical {
namespace core {

class GenericPropertyParameter
{
private:
    WithPos<std::string> name;
    std::vector<WithPos<std::string>> values;

public:
    const WithPos<std::string> &getName() const noexcept { return name; }
    const std::vector<WithPos<std::string>> &getValues() const noexcept
    {
        return values;
    }

    const WithPos<std::string> &getValue() const
    {
        if (values.size() > 1) {
            throw ParserException(values.at(1).pos(),
                                  "Only a single property value expected!");
        }
        /* sanity check: */
        if (values.size() == 0) {
            throw std::logic_error("Generic property parameter shouldn't have no values!");
        }
        return values[0];
    }

    GenericPropertyParameter(const WithPos<std::string> &name,
                             const std::vector<WithPos<std::string>> &values)
        : name(name), values(values)
    {
    }

    GenericPropertyParameter(WithPos<std::string> &&name,
                             std::vector<WithPos<std::string>> &&values)
        : name(std::move(name)), values(std::move(values))
    {
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_GENERICPROPERTYPARAMETER_H
