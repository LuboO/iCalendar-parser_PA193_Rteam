#include "data/datetime.h"

#include "parserexception.h"

namespace ical {
namespace data {

void DateTime::print(std::ostream &out) const
{
    date.print(out);
    if (timeValid) {
        out << 'T';
        time.print(out);
    }
}

static const std::size_t DATE_LENGTH = 8;

DateTime DateTime::parse(const StreamPos &pos,
                         std::string::const_iterator begin,
                         std::string::const_iterator end,
                         bool timeIsOptional)
{
    if (static_cast<std::size_t>(end - begin) <
            DATE_LENGTH + (timeIsOptional ? 1 : 0)) {
        throw ParserException(pos, "Invalid datetime value!");
    }
    Date date = Date::parse(pos, begin, begin + DATE_LENGTH);
    begin += DATE_LENGTH;
    if (timeIsOptional && begin == end) {
        return DateTime { date };
    }
    /* If execution gets here, then either:
     * timeIsOptional == false (therefore total length is >= DATE_LENGTH + 1)
     * OR
     * timeIsOptional == true && begin != end  (end - begin >= 1)
     * In both cases, it is safe to read from begin here:
     */
    if (*begin != 'T') {
        throw ParserException(pos, "Invalid datetime value!");
    }
    Time time = Time::parse(pos, begin + 1, end);
    return { date, time };
}

} // namespace data
} // namespace ical

