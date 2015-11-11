#include "tests/dateparsertests.h"

#include "data/date.h"

#include "tests/dataparserutils.h"

#include <vector>

namespace ical {
namespace tests {

static const std::vector<std::pair<bool, std::string>> VALIDATION {
    /* year range: */
    { true,  "99990101" },
    { true,  "00000101" },

    /* leap year rules: */
    { true,  "20000229" },
    { false, "20030229" },
    { true,  "20040229" },
    { false, "21000229" },

    /* month range: */
    { false, "20150001" },
    { true,  "20150101" },
    { true,  "20151201" },
    { false, "20151301" },

    /* month day ranges: */
    { false, "20150100" },
    { true,  "20150101" },
    { true,  "20150131" },
    { false, "20150132" },
    { true,  "20150228" },
    { false, "20150229" },
    { false, "20150230" },
    { true,  "20150331" },
    { false, "20150332" },
    { true,  "20150430" },
    { false, "20150431" },
    { true,  "20150531" },
    { false, "20150532" },
    { true,  "20150630" },
    { false, "20150631" },
    { true,  "20150731" },
    { false, "20150732" },
    { true,  "20150831" },
    { false, "20150832" },
    { true,  "20150930" },
    { false, "20150931" },
    { true,  "20151031" },
    { false, "20151032" },
    { true,  "20151130" },
    { false, "20151131" },
    { true,  "20151231" },
    { false, "20151232" },

    /* invalid characters/length: */
    { false, "abcdefgh" },
    { false, "201x0101" },
    { false, "2015x101" },
    { false, "2015010x" },
    { false, "2015010" },
    { false, "x20150101" },
    { false, "20150101x" },
};

void DateParserTests::runTests(TestReporter &tr)
{
    tr.reportTestSuite("data::Date::parse");
    for (auto &val : VALIDATION) {
        bool valid = DataParserUtils::tryParse<data::Date>(val.second);
        tr.registerTest("Is '" + val.second + "' valid?",
                        val.first, valid);
    }
    tr.endTestSuite();
}

} // namespace tests
} // namespace ical

