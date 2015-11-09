#ifndef ICAL_PROPERTIES_FREEBUSY_H
#define ICAL_PROPERTIES_FREEBUSY_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/fbtype.h"
#include "data/period.h"

namespace ical {
namespace properties {

class Freebusy
{
private:
    std::vector<data::Period> values;
    std::vector<parameters::FBType> fbtypeParam;
public:
    Freebusy() {}

    void print(std::ostream & out) const;

    static Freebusy parse(const core::WithPos<core::GenericProperty> &generic);

    const std::vector<data::Period> &getValue() const noexcept { return values; }
    const std::vector<parameters::FBType> getFBTypeParam() const noexcept { return fbtypeParam; }
};

} // namespace propertiespe
} // namespace ical

#endif // ICAL_PARAMETERS_FREEBUSY_H

