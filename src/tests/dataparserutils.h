#ifndef ICAL_TESTS_DATAPARSERUTILS_H
#define ICAL_TESTS_DATAPARSERUTILS_H

#include <sstream>

#include "parserexception.h"

namespace ical {
namespace tests {

struct DataParserUtils
{
    template<class T>
    static bool tryParse(const std::string &str)
    {
        try {
            T::parse({}, str.begin(), str.end());
            return true;
        } catch (ParserException &) {
            return false;
        }
    }

    template<class T>
    static std::string parse(const std::string &str)
    {
        std::ostringstream out;
        T::parse({}, str.begin(), str.end()).print(out);
        return out.str();
    }
};

} // namespace tests
} // namespace ical

#endif // ICAL_TESTS_DATAPARSERUTILS_H
