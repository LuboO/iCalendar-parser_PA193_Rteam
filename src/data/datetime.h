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
    Time time;

public:
    const Date &getDate() const noexcept { return date; }
    const Time &getTime() const noexcept { return time; }

    DateTime(const Date &date, const Time &time)
        : date(date), time(time)
    {
    }
    DateTime(Date &&date, Time &&time)
        : date(std::move(date)), time(std::move(time))
    {
    }

    void print(std::ostream &out);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_DATETIME_H
