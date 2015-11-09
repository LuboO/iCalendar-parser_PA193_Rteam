#ifndef ICAL_PROPERTIES_DTSTART_H
#define ICAL_PROPERTIES_DTSTART_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/tzid_param.h"
#include "parameters/value.h"
#include "data/datetime.h"

namespace ical {
namespace properties {

class DTStart
{
private:
    data::DateTime value;
    std::vector<parameters::Tzid_param> tzidParam;
    std::vector<parameters::Value> valueParam;
public:
    static const std::string NAME;

    DTStart() {}

    void print(std::ostream & out) const;
    
    static DTStart parse(const core::WithPos<core::GenericProperty> &generic);

	const data::DateTime &getValue() const noexcept { return value; }
    const std::vector<parameters::Tzid_param> &getTzidParam() const noexcept { return tzidParam; }
    const std::vector<parameters::Value> &getValueParam() const noexcept { return valueParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DTSTART_H

