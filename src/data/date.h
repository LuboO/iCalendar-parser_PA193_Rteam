#ifndef ICAL_DATA_DATE_H
#define ICAL_DATA_DATE_H

#include "streampos.h"

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
    unsigned int getYear() const noexcept { return year; }
    unsigned int getMonth() const noexcept { return month; }
    unsigned int getDay() const noexcept { return day; }

    Date() { }

    Date(unsigned int year, unsigned int month, unsigned int day)
        : year(year), month(month), day(day)
    {
    }

    void print(std::ostream &out) const;

    static Date parse(const StreamPos &pos,
                      std::string::const_iterator begin,
                      std::string::const_iterator end);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_DATE_H
