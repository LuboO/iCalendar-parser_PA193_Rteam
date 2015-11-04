#ifndef ICAL_DATA_DATETIME_H
#define ICAL_DATA_DATETIME_H

#include "data/date.h"
#include "data/time.h"

#include <memory>

namespace ical {
namespace data {

class DateTime
{
private:
    Date date;
    bool timeValid;
    Time time;

public:
    const Date &getDate() const noexcept { return date; }

    bool hasTime() const noexcept { return timeValid; }
    const Time &getTime() const
    {
        if (!timeValid) {
            throw std::logic_error("Time not set!");
        }
        return time;
    }

    DateTime() { }

    DateTime(const Date &date)
        : date(date), timeValid(false), time()
    {
    }
    DateTime(Date &&date)
        : date(std::move(date)), timeValid(false), time()
    {
    }

    DateTime(const Date &date, const Time &time)
        : date(date), timeValid(true), time(time)
    {
    }
    DateTime(Date &&date, Time &&time)
        : date(std::move(date)), timeValid(true), time(std::move(time))
    {
    }

    void print(std::ostream &out) const;
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_DATETIME_H
