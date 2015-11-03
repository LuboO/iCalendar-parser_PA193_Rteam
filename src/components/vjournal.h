#ifndef ICAL_COMPONENTS_VJOURNAL_H
#define ICAL_COMPONENTS_VJOURNAL_H

#include "core/genericcomponent.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VJournal
{
private:

public:
    VJournal() {}

    void print(std::ostream &out) const;

    static VJournal parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VJOURNAL_H
