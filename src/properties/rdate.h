#ifndef ICAL_PROPERTIES_rdate_H
#define ICAL_PROPERTIES_rdate_H

#include <ostream>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "data/datetime.h"
#include "data/period.h"

#include "parameters/tzid_param.h"

namespace ical {
namespace properties {

class RDate
{
private:
    std::vector<data::DateTime> dts;
    std::vector<data::Period> periods;

    std::vector<parameters::Tzid_param> tzid;

public:
    /**
     * Gets a value indicating whether this instance contains a vector
     * of periods or a vector of date-times.
     *
     * If this function returns `true`, then `getDateTimes` returns an empty
     * vector. If it returns `false`, then `getPeriods` returns an empty vector.
     *
     * @return `true` if this instance contains periods, `false` if it
     *      contains date-times
     */
    bool hasPeriods() const noexcept { return dts.empty(); }

    const std::vector<data::DateTime> &getDateTimes() const noexcept
    {
        return dts;
    }
    const std::vector<data::Period> &getPeriods() const noexcept
    {
        return periods;
    }

    const std::vector<parameters::Tzid_param> &getTzidParam() const noexcept
    {
        return tzid;
    }

    RDate() : dts(), periods(), tzid()
    {
    }

    RDate(std::vector<data::DateTime> &&values,
          std::vector<parameters::Tzid_param> &&tzid)
        : dts(std::move(values)), periods(), tzid(std::move(tzid))
    {
    }

    RDate(std::vector<data::Period> &&values,
          std::vector<parameters::Tzid_param> &&tzid)
        : dts(), periods(std::move(values)), tzid(std::move(tzid))
    {
    }

    void print(std::ostream &out) const;

    static RDate parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_rdate_H

