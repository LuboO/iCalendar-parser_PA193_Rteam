#ifndef ICAL_PARSERTEMPLATE_H
#define ICAL_PARSERTEMPLATE_H

#include "core/genericparsertemplate.h"
#include "components/vcalendar.h"

namespace ical {

class ParserTemplate
{
public:
    template<class InputCharIterator>
    static std::vector<components::VCalendar> parseIterators(
            InputCharIterator begin, InputCharIterator end)
    {
        auto genericComps = std::move(
                    core::GenericParserTemplate::parseIterators(begin, end));

        std::vector<components::VCalendar> res;
        res.reserve(genericComps.size());

        for (auto &genericComp : genericComps) {
            res.push_back(std::move(components::VCalendar::parse(genericComp)));
        }
        return res;
    }
};

} // namespace ical

#endif // ICAL_PARSERTEMPLATE_H
