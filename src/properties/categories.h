#ifndef ICAL_PROPERTIES_CATEGORIES_H
#define ICAL_PROPERTIES_CATEGORIES_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Categories
{
public:
    Categories() {}

    void print(std::ostream & out) const;

    static Categories parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_CATEGORIES_H

