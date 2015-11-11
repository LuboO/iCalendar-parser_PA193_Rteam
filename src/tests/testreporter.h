#ifndef ICAL_TESTS_TESTREPORTER_H
#define ICAL_TESTS_TESTREPORTER_H

#include <string>
#include <iostream>

namespace ical {
namespace tests {

class TestReporter
{
private:
    unsigned int testsFailed = 0;
    unsigned int testsTotal = 0;

    unsigned int suiteFailed = 0;
    unsigned int suiteTotal = 0;

public:
    unsigned int getTestsFailed() const noexcept { return testsFailed; }
    unsigned int getTestsTotal() const noexcept { return testsTotal; }

    TestReporter() { }

    void reportTestSuite(const std::string &name)
    {
        std::cerr << "RUNNING TEST SUITE '" + name + "'..." << std::endl;
    }
    void endTestSuite()
    {
        if (testsFailed != 0) {
            std::cerr << "  TESTS FAILED! " << suiteFailed << "/"
                      << suiteTotal << " tests failed." << std::endl;
        } else {
            std::cerr << "  ALL " << suiteTotal << " TESTS SUCCEEDED!" << std::endl;
        }
        suiteFailed = 0;
        suiteTotal = 0;
    }

    void registerTest(const std::string &name, bool result)
    {
        if (!result) {
            std::cerr << "  TEST FAILED: '" << name
                      << "'" << std::endl;
            ++testsFailed;
            ++suiteFailed;
        }
        ++testsTotal;
        ++suiteTotal;
    }

    template<class T>
    void registerTest(const std::string &name, const T &expected, const T &actual)
    {
        if (actual != expected) {
            std::cerr << "  TEST FAILED: '" << name
                      << "' - expected value: " << expected
                      << ", actual value: " << actual << std::endl;
            ++testsFailed;
            ++suiteFailed;
        }
        ++testsTotal;
        ++suiteTotal;
    }

    int reportFinalResults()
    {
        if (testsFailed != 0) {
            std::cerr << "TESTS FAILED! " << testsFailed << "/"
                      << testsTotal << " tests failed." << std::endl;
        } else {
            std::cerr << "ALL " << testsTotal << " TESTS SUCCEEDED!" << std::endl;
        }
        /* clamp failed tests for exit code: */
        return testsFailed > 255 ? 255 : testsFailed;
    }
};

} // namespace tests
} // namespace ical

#endif // ICAL_TESTS_TESTREPORTER_H
