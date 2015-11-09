#ifndef ICAL_PROPERTIES_TRANSP_H
#define ICAL_PROPERTIES_TRANSP_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Transp
{
private:
    std::string value;
public:
    Transp() {}

    void print(std::ostream & out) const;

    static Transp parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TRANSP_H

