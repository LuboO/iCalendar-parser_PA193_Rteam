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
    const DateTime &getEndTime() const
    {
        if (!explicit_) {
            throw std::logic_error("Period not explicit!");
        }
        return end;
    }
    /* invalid if isExplicit() returns true: */
    const Duration &getDuration() const
    {
        if (explicit_) {
            throw std::logic_error("Period is explicit!");
        }
        return duration;
    }

    Period() : explicit_(), start(), end(), duration() { }

    Period(const DateTime &start, const DateTime &end)
        : explicit_(true), start(start), end(end), duration()
    {
    }

    Period(const DateTime &start, const Duration &duration)
        : explicit_(false), start(start), end(), duration(duration)
    {
    }

    void print(std::ostream &out) const;

    static Period parse(const StreamPos &pos,
                        std::string::const_iterator begin,
                        std::string::const_iterator end);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_PERIOD_H
