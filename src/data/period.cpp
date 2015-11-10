#include "data/period.h"

#include "parserexception.h"

#include <regex>
#include <algorithm>

namespace ical {
namespace data {

void Period::print(std::ostream &out) const
{
    start.print(out);
    out << '/';
    if (explicit_) {
        end.print(out);
    } else {
        duration.print(out);
    }
}

Period Period::parse(const StreamPos &pos,
                     std::string::const_iterator begin,
                     std::string::const_iterator end)
{
    auto slash = std::find(begin, end, '/');
    /* second part (after the slash) must have at least one character: */
    if (end - slash < 2) {
        throw ParserException(pos, "Invalid period value!");
    }
    auto startTime = DateTime::parse(pos, begin, slash);
    char firstCharOfSecondPart = *(slash + 1);
    if (firstCharOfSecondPart == '-' || firstCharOfSecondPart == '+' ||
            firstCharOfSecondPart == 'P') {
        auto duration = Duration::parse(pos, slash + 1, end);
        if (duration.isNegative()) {
            throw ParserException(pos, "Period duration must be positive!");
        }
        return { startTime, duration };
    } else {
        auto endTime = DateTime::parse(pos, slash + 1, end);
        return { startTime, endTime };
    }
}

} // namespace data
} // namespace ical

