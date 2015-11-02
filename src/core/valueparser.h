#ifndef ICAL_CORE_VALUEPARSER_H
#define ICAL_CORE_VALUEPARSER_H

#include "streampos.h"

#include "data/period.h"
#include "data/utcoffset.h"
#include "data/recurrencerule.h"

#include <string>

namespace ical {
namespace core {

class ValueParser
{
public:
    static bool parseBoolean(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static double parseFloat(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static int parseInteger(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);

    static std::string parseText(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static std::string parseCalendarAddress(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static std::string parseUri(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static std::string parseBinary(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);

    static data::Date parseDate(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::Time parseTime(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::DateTime parseDateTime(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::UTCOffset parseUTCOffset(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);

    static data::Duration parseDuration(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::Period parsePeriod(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
    static data::RecurrenceRule parseRecurrenceRule(StreamPos pos, std::string::const_iterator begin, std::string::const_iterator end);
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_VALUEPARSER_H
