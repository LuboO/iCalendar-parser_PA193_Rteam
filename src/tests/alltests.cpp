#include "tests/alltests.h"

#include "tests/dateparsertests.h"
#include "tests/durationparsertests.h"
#include "tests/varioustests.h"

namespace ical {
namespace tests {

int AllTests::run()
{
    TestReporter tr;
    try {
        DateParserTests::runTests(tr);
        DurationParserTests::runTests(tr);
        VariousTests::runTests(tr);
    } catch(std::exception &ex) {
        std::cerr << "ERROR: Exception while running tests: "
                  << ex.what() << std::endl;
    }
    return tr.reportFinalResults();
}

} // namespace tests
} // namespace ical

