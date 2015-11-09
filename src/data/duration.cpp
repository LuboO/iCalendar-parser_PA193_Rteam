#include "duration.h"

#include "parserexception.h"
#include "core/valueparser.h"

#include <regex>

namespace ical {
namespace data {

void Duration::print(std::ostream &out) const
{
    if (negative) {
        out << '-';
    }
    out << 'P';
    if (weeks != 0) {
        out << weeks << 'W';
    } else {
        out << 'T';
        out << days << "DT"
            << hours << 'H'
            << minutes << 'M'
            << seconds << 'S';
    }
}

using ValueParser = core::ValueParser;

Duration Duration::parse(const StreamPos &pos,
                         std::string::const_iterator begin,
                         std::string::const_iterator end)
{
    static const std::regex RE_DURATION_START { "([-+]?)P(?:(([0-9]+)W$)|(?:(([0-9]+)D)?(?:($)|(T))))" };
    static const std::regex RE_DURATION_TIME_INIT { "([0-9]+)(?:(H)|(M)|(S$))" };
    static const std::regex RE_DURATION_TIME_MIN { "$|([0-9]+)M" };
    static const std::regex RE_DURATION_TIME_SEC { "$|([0-9]+)S$" };

    std::smatch m;
    if (!std::regex_search(begin, end, m, RE_DURATION_START,
                          std::regex_constants::match_continuous)) {
        throw ParserException(pos, "Invalid duration value!");
    }
    begin = m[0].second;

    bool negative = m[1].length() != 0 && *m[1].first == '-';
    if (m[2].matched) {
        unsigned int weeks = ValueParser::parseUnsignedInteger(pos, m[3].first, m[3].second);
        return { negative, weeks };
    }
    unsigned int days = 0;
    unsigned int hours = 0;
    unsigned int minutes = 0;
    unsigned int seconds = 0;

    bool timeMustFollow = true;
    if (m[4].matched) {
        days = ValueParser::parseUnsignedInteger(pos, m[5].first, m[5].second);
        timeMustFollow = false;
    }
    if (m[7].matched) {
        if (!std::regex_search(begin, end, m, RE_DURATION_TIME_INIT,
                               std::regex_constants::match_continuous)) {
            throw ParserException(pos, "Invalid duration value!");
        }
        begin = m[0].second;

        bool min = false;
        bool sec = false;
        if (m[2].matched) {
            hours = ValueParser::parseUnsignedInteger(pos, m[1].first, m[1].second);
            min = true;
        } else if (m[3].matched) {
            minutes = ValueParser::parseUnsignedInteger(pos, m[1].first, m[1].second);
            sec = true;
        } else {
            seconds = ValueParser::parseUnsignedInteger(pos, m[1].first, m[1].second);
        }
        if (min) {
            /* M */
            if (!std::regex_search(begin, end, m, RE_DURATION_TIME_MIN,
                                  std::regex_constants::match_continuous)) {
                throw ParserException(pos, "Invalid duration value!");
            }
            begin = m[0].second;

            if (m[1].matched) {
                minutes = ValueParser::parseUnsignedInteger(pos, m[1].first, m[1].second);

                sec = true;
            }
        }
        if (sec) {
            /* S */
            if (!std::regex_search(begin, end, m, RE_DURATION_TIME_SEC,
                                  std::regex_constants::match_continuous)) {
                throw ParserException(pos, "Invalid duration value!");
            }
            begin = m[0].second;

            if (m[1].matched) {
                seconds = ValueParser::parseUnsignedInteger(pos, m[1].first, m[1].second);
            }
        }
    } else if (timeMustFollow) {
        throw ParserException(pos, "Invalid duration value!");
    }
    return { negative, days, hours, minutes, seconds };
}

} // namespace data
} // namespace ical

