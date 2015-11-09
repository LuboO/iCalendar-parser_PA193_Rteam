#ifndef ICAL_PARSER_H
#define ICAL_PARSER_H

#include "parserexception.h" /* for includer's convenience */

#include "components/vcalendar.h"

#include <string>
#include <istream>

namespace ical {

class Parser
{
public:
    static std::vector<components::VCalendar> parseStream(std::istream &stream);
    static std::vector<components::VCalendar> parseString(std::string::const_iterator begin,
                                                          std::string::const_iterator end);
    static std::vector<components::VCalendar> parseString(const std::string &str)
    {
        return std::move(parseString(str.begin(), str.end()));
    }
};

} // namespace ical

#endif // ICAL_PARSER_H
