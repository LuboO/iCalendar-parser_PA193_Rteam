#ifndef ICAL_PROPERTIES_METHOD_H
#define ICAL_PROPERTIES_METHOD_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Method
{
private:
    std::string value;
public:
    Method() {}

    void print(std::ostream & out) const;

    static Method parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept {return value;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_METHOD_H

