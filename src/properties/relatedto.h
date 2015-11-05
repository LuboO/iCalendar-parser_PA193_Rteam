#ifndef ICAL_PROPERTIES_RELATEDTO_H
#define ICAL_PROPERTIES_RELATEDTO_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/reltype.h"

namespace ical {
namespace properties {

class RelatedTo
{
private:
    std::string value;
    std::vector<parameters::Reltype> reltypeParam;
public:
    RelatedTo() {}

    void print(std::ostream &out) const;

    static RelatedTo parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept {return value;}
    const std::vector<parameters::Reltype> &getReltypeParam() const noexcept {return reltypeParam;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RELATEDTO_H

