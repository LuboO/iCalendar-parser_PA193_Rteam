#ifndef ICAL_PROPERTIES_exdate_H
#define ICAL_PROPERTIES_exdate_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "data/datetime.h"

#include "parameters/tzid_param.h"

namespace ical {
namespace properties {

class ExDate
{
private:
    std::vector<data::DateTime> values;

    std::vector<parameters::Tzid_param> tzid;

public:
    const std::vector<data::DateTime> &getValue() const noexcept
    {
        return values;
    }

    const std::vector<parameters::Tzid_param> &getTzidParam() const noexcept
    {
        return tzid;
    }

    ExDate() : values(), tzid()
    {
    }

    ExDate(std::vector<data::DateTime> &&values,
           std::vector<parameters::Tzid_param> &&tzid)
        : values(std::move(values)), tzid(std::move(tzid))
    {
    }

    void print(std::ostream &out) const;

    static ExDate parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_exdate_H

