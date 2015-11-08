#ifndef ICAL_CORE_VALUEPARSER_H
#define ICAL_CORE_VALUEPARSER_H

#include "streampos.h"

#include "data/period.h"
#include "data/utcoffset.h"
#include "data/recurrencerule.h"

#include <string>
#include <vector>
#include <algorithm>

namespace ical {
namespace core {

class ValueParser
{
public:
    template<class T>
    using ParseFunc = T(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);

    static bool parseBoolean(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static double parseFloat(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static int parseInteger(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static unsigned int parseUnsignedInteger(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);

    static void validateCalendarAddress(const StreamPos &pos, const std::string &value);
    static void validateUri(const StreamPos &pos, const std::string &value);

    static std::string parseText(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static std::string parseBase64(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);

    static data::Date parseDate(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::Time parseTime(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::DateTime parseDateTime(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end,
                                        bool timeIsOptional);
    static data::DateTime parseDateTime(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end)
    {
        return parseDateTime(pos, begin, end, false);
    }

    static data::UTCOffset parseUTCOffset(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);

    static data::Duration parseDuration(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::Period parsePeriod(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::RecurrenceRule parseRecurrenceRule(const StreamPos &pos, std::string::const_iterator begin, std::string::const_iterator end);

    static std::string parseQuoted(const StreamPos &pos, const std::string &value);
    static std::string parsePossiblyQuoted(const StreamPos &pos, const std::string &value);

    /**
     * Parse comma(or something else)-delimited sequence of values.
     *
     * Example:
     * ```
     * // parses a ';'-separated sequence of integers (like '1;2;3'):
     * // NOTE: The template argument is inferred automatically,
     * // so you don't have to specify it explicitly.
     * std::vector<int> ints = ValueParser::parseDelimited(
     *                              pos, begin, end,
     *                              ValueParser::parseInteger, ';');
     * ```
     */
    template<class T>
    static std::vector<T> parseDelimited(
            const StreamPos &pos,
            std::string::const_iterator begin,
            std::string::const_iterator end,
            ParseFunc<T> elemParseFunc, char delimiter = ',')
    {
        std::vector<T> res;
        std::string::const_iterator delimIt;
        std::string::const_iterator elemIt = begin;
        while (true) {
            delimIt = std::find(elemIt, end, delimiter);
            res.emplace_back(std::move(elemParseFunc(pos, elemIt, delimIt)));

            if (delimIt == end) {
                break;
            }
            /* skip the delimiter: */
            elemIt = delimIt + 1;
        }
        return res;
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_VALUEPARSER_H
