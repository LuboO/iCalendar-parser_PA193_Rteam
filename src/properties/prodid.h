#ifndef ICAL_PROPERTIES_PRODID_H
#define ICAL_PROPERTIES_PRODID_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class ProdId
{
private:
    std::string value;
public:
    ProdId() {}

    void print(std::ostream & out) const;

    static ProdId parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_PRODID_H

