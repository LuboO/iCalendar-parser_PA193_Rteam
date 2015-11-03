#ifndef ICAL_DATA_DATE_H
#define ICAL_DATA_DATE_H

#include <ostream>

namespace ical {
namespace data {

class Date
{
private:
    unsigned int year;
    unsigned int month;
    unsigned int day;

public:
    constexpr unsigned int getYear() const noexcept { return year; }
    constexpr unsigned int getMonth() const noexcept { return month; }
    constexpr unsigned int getDay() const noexcept { return day; }

    constexpr Date(unsigned int year, unsigned int month, unsigned int day)
        : year(year), month(month), day(day)
    {
    }

    void print(std::ostream &out) const;
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_DATE_H
