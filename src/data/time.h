#ifndef ICAL_DATA_TIME_H
#define ICAL_DATA_TIME_H

#include <ostream>

namespace ical {
namespace data {

class Time
{
private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    bool local;

public:
    constexpr unsigned int getHour() const noexcept { return hour; }
    constexpr unsigned int getMinute() const noexcept { return minute; }
    constexpr unsigned int getSecond() const noexcept { return second; }
    constexpr bool isLocal() const noexcept { return local; }

    constexpr Time(unsigned int hour, unsigned int minute,
                   unsigned int second, bool local)
        : hour(hour), minute(minute), second(second), local(local)
    {
    }

    void print(std::ostream &out);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_TIME_H
