#ifndef ICAL_PROPERTIES_URL_H
#define ICAL_PROPERTIES_URL_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Url
{
private:
    std::string value;
public:
    Url() {}

    void print(std::ostream &out) const;

    static Url parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string getValue() const noexcept {return value;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_URL_H

