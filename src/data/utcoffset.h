#ifndef ICAL_DATA_UTCOFFSET_H
#define ICAL_DATA_UTCOFFSET_H

#include <ostream>

namespace ical {
namespace data {

class UTCOffset
{
private:
    bool negative;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

public:
    bool isNegative() const noexcept { return negative; }
    unsigned int getHours() const noexcept { return hours; }
    unsigned int getMinutes() const noexcept { return minutes; }
    unsigned int getSeconds() const noexcept { return seconds; }

    UTCOffset() { }

    UTCOffset(bool negative, unsigned int hours,
              unsigned int minutes, unsigned int seconds)
        : negative(negative), hours(hours), minutes(minutes), seconds(seconds)
    {
    }

    void print(std::ostream &out) const;
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_UTCOFFSET_H
