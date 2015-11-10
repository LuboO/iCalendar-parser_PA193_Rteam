#ifndef ICAL_PROPERTIES_DURATIONPROP_H
#define ICAL_PROPERTIES_DURATIONPROP_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"
#include "data/duration.h"

namespace ical {
namespace properties {

class DurationProp
{
private:
    data::Duration value;
public:
    static const std::string NAME;

    DurationProp() {}

    void print(std::ostream & out) const;

    static DurationProp parse(const core::WithPos<core::GenericProperty> &generic);

    const data::Duration &getValue() const noexcept {return value;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DURATIONPROP_H

