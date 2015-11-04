#include "recurrencerule.h"

namespace ical {
namespace data {

void WeekdayNumber::print(std::ostream &out) const
{
    if (optWeekNumber != 0) {
        out << optWeekNumber;
    }
    out << weekday;
}

template<class T>
struct PrintHelper
{
    static void print(std::ostream &out, const T &val)
    {
        out << val;
    }
};

template<>
struct PrintHelper<WeekdayNumber>
{
    static void print(std::ostream &out, const WeekdayNumber &val)
    {
        val.print(out);
    }
};

template<class T>
static void printList(std::ostream &out, const std::string name, const std::vector<T> list)
{
    if (list.empty()) {
        return;
    }

    out << ';' << name << '=';
    PrintHelper<T>::print(out, list.front());
    for (auto it = list.begin() + 1; it < list.end(); it++) {
        out << ',';
        PrintHelper<T>::print(out, *it);
    }
}

void RecurrenceRule::print(std::ostream &out) const
{
    out << "FREQ=" << freq;
    if (limited) {
        if (limitedByCount) {
            out << ";COUNT=" << count;
        } else {
            out << ";UNTIL=";
            until.print(out);
        }
    }
    out << ";INTERVAL=" << opts.getInterval();

    printList(out, "BYSECOND", opts.getBySecond());
    printList(out, "BYMINUTE", opts.getByMinute());
    printList(out, "BYHOUR", opts.getByHour());
    printList(out, "BYDAY", opts.getByDay());
    printList(out, "BYMONTHDAY", opts.getByMonthDay());
    printList(out, "BYYEARDAY", opts.getByYearDay());
    printList(out, "BYWEEKNO", opts.getByWeekNumber());
    printList(out, "BYMONTH", opts.getByMonth());
    printList(out, "BYSETPOS", opts.getBySetPos());

    out << ";WKST=" << opts.getWeekStart();
}

} // namespace data
} // namespace ical

