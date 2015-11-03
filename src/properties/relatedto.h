#ifndef ICAL_PROPERTIES_RELATEDTO_H
#define ICAL_PROPERTIES_RELATEDTO_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class RelatedTo
{
public:
    RelatedTo() {}

    void print(std::ostream &out) const;

    static RelatedTo parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RELATEDTO_H

