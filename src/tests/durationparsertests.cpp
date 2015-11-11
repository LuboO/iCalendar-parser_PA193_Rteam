#include "tests/durationparsertests.h"

#include "tests/dataparserutils.h"

#include "data/duration.h"

#include <vector>

namespace ical {
namespace tests {

static const std::vector<std::pair<bool, std::string>> VALIDATION {
    { true, "P10W" },
    { true, "P12D" },
    { true, "PT12H" },
    { true, "PT12M" },
    { true, "PT12S" },
    { true, "P12DT12H" },
    { true, "PT12H12M" },
    { true, "PT12H12M50S" },

    { false, "P" },
    { false, "xxxxP10W" },
    { false, "P12DT" },
    { false, "P10WT10M" },
    { false, "P10W10D" },
    { false, "PT10M10W" },
};

void DurationParserTests::runTests(TestReporter &tr)
{
    tr.reportTestSuite("data::Duration::parse");
    for (auto &val : VALIDATION) {
        bool valid = DataParserUtils::tryParse<data::Duration>(val.second);
        tr.registerTest("Is '" + val.second + "' valid?",
                        val.first, valid);
    }
    tr.endTestSuite();
}

} // namespace tests
} // namespace ical

