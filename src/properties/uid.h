#ifndef ICAL_PROPERTIES_UID_H
#define ICAL_PROPERTIES_UID_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Uid
{
private:
    std::string value;
public:
    static const std::string NAME;

    Uid() {}

    void print(std::ostream &out) const;

    static Uid parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string getValue() const noexcept {return value;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_UID_H

