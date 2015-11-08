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
    unsigned int seqNum;

public:
    unsigned int getValue() const noexcept { return seqNum; }

    Sequence() : seqNum(0)
    {
    }
    Sequence(unsigned int seqNum) : seqNum(seqNum)
    {
    }

    void print(std::ostream &out) const;

    static Sequence parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_sequence_H

