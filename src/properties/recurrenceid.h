#ifndef ICAL_PROPERTIES_RECURRENCEID_H
#define ICAL_PROPERTIES_RECURRENCEID_H

#include <ostream>
#include <vector>

#include "parserexception.h"
#include "core/genericproperty.h"

#include "data/datetime.h"

#include "parameters/value.h"
#include "parameters/tzid_param.h"
#include "parameters/range.h"

namespace ical {
namespace properties {

class RecurrenceId
{
private:
    data::DateTime value;
    std::vector<parameters::Value> valueParam;
    std::vector<parameters::Tzid_param> tzidParam;
    std::vector<parameters::Range> rangeParam;
public:
    static const std::string NAME;

    RecurrenceId() {}

    void print(std::ostream &out) const;

    static RecurrenceId parse(const core::WithPos<core::GenericProperty> &generic);

    const data::DateTime &getValue() const noexcept {return value;}
    const std::vector<parameters::Value> &getValueParam() const noexcept {return valueParam;}
    const std::vector<parameters::Tzid_param> &getTzidParam() const noexcept {return tzidParam;}
    const std::vector<parameters::Range> &getRangeParam() const noexcept {return rangeParam;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RECURRENCEID_H

