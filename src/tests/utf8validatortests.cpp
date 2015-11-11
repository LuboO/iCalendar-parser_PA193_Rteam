#include "tests/utf8validatortests.h"

#include "core/utf8validator.h"

#include <vector>

namespace ical {
namespace tests {

static const std::vector<std::pair<bool, std::string>> VALIDATION {
    { false, "\xC1\xBF" },
    { true,  "\xC2\x80" },
    { true,  "\xDF\xBF" },

    { false, "\xE0\x9F\xBF" },
    { true,  "\xE0\xA0\x80" },
    { true,  "\xEF\xBF\xBF" },

    { false, "\xF0\x8F\xBF\xBF" },
    { true,  "\xF0\x90\x80\x80" },
    { true,  "\xF0\x90\x80\x80" },
    { true,  "\xF4\x8F\xBF\xBF" },
    { false, "\xF4\x90\x80\x80" },
    { false, "\xF7\xBF\xBF\xBF" },

    { false, "\x80" },
    { false, "\xBF" },
    { false, "\xC2" },
    { false, "\xE0" },
    { false, "\xE0\xA0" },
    { false, "\xF0" },
    { false, "\xF0\x90" },
    { false, "\xF0\x90\x80" },
};

static bool validateUTF8String(const std::string &str)
{
    core::UTF8Validator validator;
    for (char c : str) {
        if (!validator.checkNext(c)) {
            return false;
        }
    }
    return validator.checkEnd();
}

void UTF8ValidatorTests::runTests(TestReporter &tr)
{
    tr.reportTestSuite("UTF-8 validator tests");
    for (auto &val : VALIDATION) {
        bool valid = validateUTF8String(val.second);
        tr.registerTest("Is '" + val.second + "' valid?",
                        val.first, valid);
    }
    tr.endTestSuite();
}

} // namespace tests
} // namespace ical

