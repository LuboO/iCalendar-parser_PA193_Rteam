#include "parser.h"

#include "parsertemplate.h"

namespace ical {

std::vector<components::VCalendar>
Parser::parseStream(std::istream &stream)
{
    return std::move(ParserTemplate::parseIterators(
                         std::istreambuf_iterator<char>(stream),
                         std::istreambuf_iterator<char>()));
}

std::vector<components::VCalendar>
Parser::parseString(std::string::const_iterator begin,
                           std::string::const_iterator end)
{
    return std::move(ParserTemplate::parseIterators(begin, end));
}

} // namespace ical

