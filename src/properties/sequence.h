#ifndef ICAL_PROPERTIES_sequence_H
#define ICAL_PROPERTIES_sequence_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Sequence
{
private:
    // TODO

public:
    Sequence() {}

    void print(std::ostream &out) const;

    static Sequence parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_sequence_H

