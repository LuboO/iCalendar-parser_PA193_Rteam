#ifndef ICAL_PROPERTIES_COMPLETED_H
#define ICAL_PROPERTIES_COMPLETED_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"
#include "data/datetime.h"

namespace ical {
namespace properties {

class Completed
{
private:
    data::DateTime value;
public:
    static const std::string NAME;

    Completed() {}

    void print(std::ostream & out) const;

    static Completed parse(const core::WithPos<core::GenericProperty> &generic);

    const data::DateTime &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_COMPLETED_H

