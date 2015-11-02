#ifndef ICAL_DATA_RECURRENCERULE_H
#define ICAL_DATA_RECURRENCERULE_H

#include <ostream>

namespace ical {
namespace data {

// TODO: finish this
class RecurrenceRule
{
public:
    RecurrenceRule() { }

    void print(std::ostream &out);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_RECURRENCERULE_H
