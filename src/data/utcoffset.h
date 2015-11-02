#ifndef ICAL_DATA_UTCOFFSET_H
#define ICAL_DATA_UTCOFFSET_H

#include <ostream>

namespace ical {
namespace data {

// TODO: finish this
class UTCOffset
{
public:
    UTCOffset() { }

    void print(std::ostream &out);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_UTCOFFSET_H
