#ifndef ICAL_COMPONENTS_VTODO_H
#define ICAL_COMPONENTS_VTODO_H

#include "core/genericcomponent.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VTodo
{
private:

public:
    VTodo() {}

    void print(std::ostream &out);

    static VTodo parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VTODO_H
