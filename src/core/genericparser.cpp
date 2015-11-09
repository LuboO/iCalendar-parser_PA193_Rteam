#include "core/genericparser.h"

#include "core/genericparsertemplate.h"

namespace ical {
namespace core {

std::vector<WithPos<GenericComponent>>
GenericParser::parseStream(std::istream &stream)
{
    return std::move(GenericParserTemplate::parseIterators(
                         std::istreambuf_iterator<char>(stream),
                         std::istreambuf_iterator<char>()));
}

std::vector<WithPos<GenericComponent>>
GenericParser::parseString(std::string::const_iterator begin,
                           std::string::const_iterator end)
{
    return std::move(GenericParserTemplate::parseIterators(begin, end));
}

} // namespace core
} // namespace ical

