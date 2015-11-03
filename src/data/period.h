#ifndef ICAL_DATA_PERIOD_H
#define ICAL_DATA_PERIOD_H

#include "data/datetime.h"
#include "data/duration.h"

namespace ical {
namespace data {

class Period
{
private:
    bool explicit_;

    DateTime start;
    DateTime end;
    Duration duration;

public:
    bool isExplicit() const noexcept { return explicit_; }

    const DateTime &getStartTime() const noexcept { return start; }
    /* invalid if isExplicit() returns false: */
    const DateTime &getEndTime() const noexcept { return start; }
    /* invalid if isExplicit() returns true: */
    const Duration &getDuration() const noexcept { return duration; }

    Period(const DateTime &start, const DateTime &end)
        : start(start), end(end), duration(false, 0, 0, 0, 0, 0)
    {
    }
    Period(DateTime &&start, DateTime &&end)
        : start(std::move(start)), end(std::move(end)),
          duration(false, 0, 0, 0, 0, 0)
    {
    }

    Period(const DateTime &start, const Duration &duration)
        : start(start), end(Date { 0, 0, 0 }, Time { 0, 0, 0, false }),
          duration(duration)
    {
    }
    Period(DateTime &&start, Duration &&duration)
        : start(std::move(start)), end(Date { 0, 0, 0 }, Time { 0, 0, 0, false }),
          duration(std::move(duration))
    {
    }

    void print(std::ostream &out) const;
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_PERIOD_H
