#ifndef ICAL_DATA_RECURRENCERULE_H
#define ICAL_DATA_RECURRENCERULE_H

#include "data/datetime.h"

#include <ostream>
#include <vector>

namespace ical {
namespace data {

class WeekdayNumber
{
private:
    /* 0 if not specified */
    int optWeekNumber;
    std::string weekday;

public:
    int getWeekNumber() const noexcept { return optWeekNumber; }
    const std::string &getWeekday() const noexcept { return weekday; }

    WeekdayNumber(int optWeekNumber, const std::string &weekday)
        : optWeekNumber(optWeekNumber), weekday(weekday)
    {
    }
    WeekdayNumber(int optWeekNumber, std::string &&weekday)
        : optWeekNumber(optWeekNumber), weekday(std::move(weekday))
    {
    }

    void print(std::ostream &out) const;

    static WeekdayNumber parse(const StreamPos &pos,
                               std::string::const_iterator begin,
                               std::string::const_iterator end);
};

class RecurrenceRuleOptions
{
private:
    unsigned int interval;

    std::vector<unsigned int> bySecond;
    std::vector<unsigned int> byMinute;
    std::vector<unsigned int> byHour;
    std::vector<WeekdayNumber> byDay;
    std::vector<int> byMonthDay;
    std::vector<int> byYearDay;
    std::vector<int> byWeekNumber;
    std::vector<int> byMonth;
    std::vector<int> bySetPos;

    std::string weekStart;

public:
    unsigned int getInterval() const noexcept { return interval; }

    const std::vector<unsigned int> &getBySecond() const noexcept
    {
        return bySecond;
    }
    const std::vector<unsigned int> &getByMinute() const noexcept
    {
        return byMinute;
    }
    const std::vector<unsigned int> &getByHour() const noexcept
    {
        return byHour;
    }
    const std::vector<WeekdayNumber> &getByDay() const noexcept
    {
        return byDay;
    }
    const std::vector<int> &getByMonthDay() const noexcept
    {
        return byMonthDay;
    }
    const std::vector<int> &getByYearDay() const noexcept
    {
        return byYearDay;
    }
    const std::vector<int> &getByWeekNumber() const noexcept
    {
        return byWeekNumber;
    }
    const std::vector<int> &getByMonth() const noexcept
    {
        return byMonth;
    }
    const std::vector<int> &getBySetPos() const noexcept
    {
        return bySetPos;
    }

    const std::string &getWeekStart() const noexcept { return weekStart; }

    RecurrenceRuleOptions(
            unsigned int interval,
            const std::vector<unsigned int> &bySecond,
            const std::vector<unsigned int> &byMinute,
            const std::vector<unsigned int> &byHour,
            const std::vector<WeekdayNumber> &byDay,
            const std::vector<int> &byMonthDay,
            const std::vector<int> &byYearDay,
            const std::vector<int> &byWeekNumber,
            const std::vector<int> &byMonth,
            const std::vector<int> &bySetPos,
            const std::string &weekStart)
        : interval(interval), bySecond(bySecond), byMinute(byMinute),
          byHour(byHour), byDay(byDay), byMonthDay(byMonthDay),
          byYearDay(byYearDay), byWeekNumber(byWeekNumber), byMonth(byMonth),
          bySetPos(bySetPos), weekStart(weekStart)
    {
    }
    RecurrenceRuleOptions(
            unsigned int interval,
            std::vector<unsigned int> &&bySecond,
            std::vector<unsigned int> &&byMinute,
            std::vector<unsigned int> &&byHour,
            std::vector<WeekdayNumber> &&byDay,
            std::vector<int> &&byMonthDay,
            std::vector<int> &&byYearDay,
            std::vector<int> &&byWeekNumber,
            std::vector<int> &&byMonth,
            std::vector<int> &&bySetPos,
            std::string &&weekStart)
        : interval(interval), bySecond(std::move(bySecond)),
          byMinute(std::move(byMinute)), byHour(std::move(byHour)),
          byDay(std::move(byDay)), byMonthDay(std::move(byMonthDay)),
          byYearDay(std::move(byYearDay)),
          byWeekNumber(std::move(byWeekNumber)), byMonth(std::move(byMonth)),
          bySetPos(std::move(bySetPos)), weekStart(std::move(weekStart))
    {
    }
};

class RecurrenceRule
{
private:
    std::string freq;

    bool limited;
    bool limitedByCount;
    DateTime until;
    unsigned int count;

    RecurrenceRuleOptions opts;

public:
    const std::string &getFrequency() const noexcept { return freq; }

    bool isLimited() const noexcept { return limited; }
    bool isLimitedByCount() const noexcept { return limitedByCount; }
    const DateTime &getEndDate() const
    {
        if (!limited) {
            throw std::logic_error("Recurrence not limited!");
        }
        if (limitedByCount) {
            throw std::logic_error("Recurrence limited by count, not end date!");
        }
        return until;
    }
    unsigned int getCount() const
    {
        if (!limited) {
            throw std::logic_error("Recurrence not limited!");
        }
        if (!limitedByCount) {
            throw std::logic_error("Recurrence limited by end date, not count!");
        }
        return count;
    }

    const RecurrenceRuleOptions &getOptions() const noexcept { return opts; }

    RecurrenceRule(const std::string &freq,
                   const RecurrenceRuleOptions &opts)
        : freq(freq), limited(false), limitedByCount(false), until(),
          count(0), opts(opts)
    {
    }
    RecurrenceRule(std::string &&freq,
                   RecurrenceRuleOptions &&opts)
        : freq(std::move(freq)), limited(false), limitedByCount(false),
          until(), count(0), opts(std::move(opts))
    {
    }

    RecurrenceRule(const std::string &freq,
                   const DateTime &until,
                   const RecurrenceRuleOptions &opts)
        : freq(freq), limited(true), limitedByCount(false), until(until),
          count(0), opts(opts)
    {
    }
    RecurrenceRule(std::string &&freq,
                   DateTime &&until,
                   RecurrenceRuleOptions &&opts)
        : freq(std::move(freq)), limited(true), limitedByCount(false),
          until(std::move(until)), count(0), opts(std::move(opts))
    {
    }

    RecurrenceRule(const std::string &freq,
                   unsigned int count,
                   const RecurrenceRuleOptions &opts)
        : freq(freq), limited(true), limitedByCount(true), until(),
          count(count), opts(opts)
    {
    }
    RecurrenceRule(std::string &&freq,
                   unsigned int count,
                   RecurrenceRuleOptions &&opts)
        : freq(std::move(freq)), limited(true), limitedByCount(false), until(),
          count(count), opts(std::move(opts))
    {
    }

    void print(std::ostream &out) const;

    static RecurrenceRule parse(const StreamPos &pos,
                                std::string::const_iterator begin,
                                std::string::const_iterator end);
};

} // namespace data
} // namespace ical

#endif // ICAL_DATA_RECURRENCERULE_H
