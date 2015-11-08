#ifndef ICAL_PROPERTIES_created_H
#define ICAL_PROPERTIES_created_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "data/datetime.h"

namespace ical {
namespace properties {

class Created
{
private:
    data::DateTime value;

public:
    const data::DateTime &getValue() const noexcept
    {
        return value;
    }

    Created(data::DateTime &&value) : value(std::move(value))
    {
    }

    void print(std::ostream &out) const;

    static Created parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_created_H

