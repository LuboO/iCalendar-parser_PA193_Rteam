#ifndef ICAL_DATA_TIME_H
#define ICAL_DATA_TIME_H

#include "streampos.h"

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
    unsigned int getHour() const noexcept { return hour; }
    unsigned int getMinute() const noexcept { return minute; }
    unsigned int getSecond() const noexcept { return second; }
    bool isLocal() const noexcept { return local; }

    Time() { }

    Time(unsigned int hour, unsigned int minute, unsigned int second,
         bool local)
        : hour(hour), minute(minute), second(second), local(local)
    {
    }

    void print(std::ostream &out) const;

    static Time parse(const StreamPos &pos,
                      std::string::const_iterator begin,
                      std::string::const_iterator end);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_TIME_H
