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
    data::DateTime dateTimeValue;
    data::Date dateValue;
    std::vector<parameters::Value> valueParam;
    std::vector<parameters::Tzid_param> tzidParam;
    std::vector<parameters::Range> rangeParam;
public:
    RecurrenceId() {}

    void print(std::ostream &out) const;

    static RecurrenceId parse(const core::WithPos<core::GenericProperty> &generic);

    bool isDate() const
    {
        return !valueParam.empty() && valueParam[0].getValue() == "DATE";
    }

    const data::DateTime &getDateTimeValue() const
    {
        if (isDate()) {
            throw std::logic_error("The property has a date value!");
        }
        return dateTimeValue;
    }
    const data::Date &getDateValue() const
    {
        if (!isDate()) {
            throw std::logic_error("The property has a date-time value!");
        }
        return dateValue;
    }
    const std::vector<parameters::Value> &getValueParam() const noexcept {return valueParam;}
    const std::vector<parameters::Tzid_param> &getTzidParam() const noexcept {return tzidParam;}
    const std::vector<parameters::Range> &getRangeParam() const noexcept {return rangeParam;}
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RECURRENCEID_H

