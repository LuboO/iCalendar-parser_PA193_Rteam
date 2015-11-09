#ifndef ICAL_TESTS_TESTREPORTER_H
#define ICAL_TESTS_TESTREPORTER_H

#include <string>
#include <iostream>

namespace ical {
namespace tests {

class TestReporter
{
private:
    unsigned int tests_failed = 0;
    unsigned int tests_total = 0;

public:
    unsigned int getTestsFailed() const noexcept { return tests_failed; }
    unsigned int getTestsTotal() const noexcept { return tests_total; }

    TestReporter() { }

    void reportTestSuite(const std::string &name)
    {
        std::cerr << "RUNNING TEST SUITE '" + name + "'..." << std::endl;
    }

    void registerTest(const std::string &name, bool result)
    {
        if (!result) {
            std::cerr << "  TEST FAILED: '" << name
                      << "'" << std::endl;
            ++tests_failed;
        }
        ++tests_total;
    }

    template<class T>
    void registerTest(const std::string &name, const T &expected, const T &actual)
    {
        if (actual != expected) {
            std::cerr << "  TEST FAILED: '" << name
                      << "' - expected value: " << expected
                      << ", actual value: " << actual << std::endl;
            ++tests_failed;
        }
        ++tests_total;
    }

    int reportFinalResults()
    {
        if (tests_failed != 0) {
            std::cerr << "TESTS FAILED! " << tests_failed << "/"
                      << tests_total << " tests failed." << std::endl;
        } else {
            std::cerr << "ALL TESTS SUCCEEDED!" << std::endl;
        }
        /* clamp failed tests for exit code: */
        return tests_failed > 255 ? 255 : tests_failed;
    }
};

} // namespace tests
} // namespace ical

#endif // ICAL_TESTS_TESTREPORTER_H
