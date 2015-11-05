#ifndef ICAL_PROPERTIES_action_H
#define ICAL_PROPERTIES_action_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Action
{
private:
    // TODO

public:
    Action() {}

    void print(std::ostream &out) const;

    static Action parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_action_H

