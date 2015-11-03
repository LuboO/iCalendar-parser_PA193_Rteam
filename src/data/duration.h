#ifndef ICAL_DATA_DURATION_H
#define ICAL_DATA_DURATION_H

#include <ostream>

namespace ical {
namespace data {

class Duration
{
private:
    bool negative;
    unsigned int weeks;
    unsigned int days;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

public:
    constexpr bool isNegative() const noexcept { return negative; }
    constexpr unsigned int getWeeks() const noexcept { return weeks; }
    constexpr unsigned int getDays() const noexcept { return days; }
    constexpr unsigned int getHours() const noexcept { return hours; }
    constexpr unsigned int getMinutes() const noexcept { return minutes; }
    constexpr unsigned int getSeconds() const noexcept { return seconds; }

    constexpr Duration(bool negative, unsigned int weeks, unsigned int days,
             unsigned int hours, unsigned int minutes, unsigned int seconds)
        : negative(negative), weeks(weeks), days(days),
          hours(hours), minutes(minutes), seconds(seconds)
    {
    }

    void print(std::ostream &out) const;
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_DURATION_H
