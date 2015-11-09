#ifndef ICAL_PROPERTIES_lastmodified_H
#define ICAL_PROPERTIES_lastmodified_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "data/datetime.h"

namespace ical {
namespace properties {

class LastModified
{
private:
    data::DateTime value;

public:
    static const std::string NAME;

    const data::DateTime &getValue() const noexcept
    {
        return value;
    }

    LastModified(data::DateTime &&value) : value(std::move(value))
    {
    }

    void print(std::ostream &out) const;

    static LastModified parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_lastmodified_H

