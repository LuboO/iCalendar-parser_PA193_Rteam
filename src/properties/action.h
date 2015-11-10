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
    std::string value;

public:
    static const std::string NAME;

    const std::string &getValue() { return value; }

    explicit Action(std::string &&value) : value(std::move(value))
    {
    }

    void print(std::ostream &out) const;

    static Action parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_action_H

