#ifndef ICAL_PROPERTIES_DUE_H
#define ICAL_PROPERTIES_DUE_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/tzid_param.h"
#include "parameters/value.h"
#include "data/datetime.h"


namespace ical {
namespace properties {

class Due
{
private:
    data::DateTime value;
    std::vector<parameters::Tzid_param> tzidParam;
    std::vector<parameters::Value> valueParam;
public:
    static const std::string NAME;

    Due() {}

    void print(std::ostream & out) const;

    static Due parse(const core::WithPos<core::GenericProperty> &generic);

    const data::DateTime &getValue() const noexcept { return value; }
    const std::vector<parameters::Tzid_param> &getTzidParam() const noexcept { return tzidParam; }
    const std::vector<parameters::Value> &getValueParam() const noexcept { return valueParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DUE_H

