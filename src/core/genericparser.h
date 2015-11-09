#ifndef ICAL_CORE_GENERICPARSER_H
#define ICAL_CORE_GENERICPARSER_H

#include "core/genericcomponent.h"

namespace ical {
namespace core {

/** A parser that parses the generic structure of an iCalendar file */
class GenericParser
{
public:
    static std::vector<WithPos<GenericComponent>> parseStream(std::istream &stream);
    static std::vector<WithPos<GenericComponent>> parseString(std::string::const_iterator begin,
                                                              std::string::const_iterator end);
    static std::vector<WithPos<GenericComponent>> parseString(const std::string &str)
    {
        return std::move(parseString(str.begin(), str.end()));
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_GENERICPARSER_H
