//#define RUN_TESTS
#ifdef RUN_TESTS

#include "tests/alltests.h"

#else /* RUN_TESTS */

#include "parser.h"

#include <memory>
#include <iostream>
#include <fstream>

static void printUsage(const char *progname)
{
    std::cerr << "Usage: " << progname << " [FILE]" << std::endl
              << std::endl
              << "  Parses the given iCalendar file and outputs its contents." << std::endl
              << std::endl
              << "Arguments:" << std::endl
              << "  FILE - the input file (stdin if not specified)" << std::endl;
}

#endif /* RUN_TESTS */

using namespace ical;

int main(int argc, const char * const *argv)
{
#ifdef RUN_TESTS
    /* quench unused variable warnings: */
    (void)argc;
    (void)argv;

    return tests::AllTests::run();
#else
    if (argc > 2) {
        std::cerr << "ERROR: Too many arguments!" << std::endl
                  << std::endl;
        printUsage(argv[0]);
        return 2;
    }

    std::istream *in = &std::cin;
    std::ifstream file;
    if (argc == 2) {
        file.open(argv[1]);
        if (file.fail()) {
            std::cerr << "ERROR: Unable to open file!" << std::endl;
            return 2;
        }
        in = dynamic_cast<std::istream *>(&file);
    }

    std::vector<components::VCalendar> objects;
    try {
        in->exceptions();
        objects = std::move(Parser::parseStream(*in));
    } catch (ParserException &ex) {
        std::cerr << "ERROR: ParserException: " << ex.what() << std::endl;
        return 1;
    } catch (std::bad_alloc &) {
        std::cerr << "ERROR: Memory allocation failed!" << std::endl;
        return 2;
    } catch (std::ios::failure &ex) {
        std::cerr << "ERROR: I/O error: " << ex.what() << std::endl;
        return 2;
    } catch (std::exception &ex) {
        std::cerr << "ERROR: Unknown  exception: " << ex.what() << std::endl;
        return 2;
    }

    try {
        std::cout.exceptions();

        for (auto &obj : objects) {
            obj.print(std::cout);
        }
    } catch (std::ios::failure &ex) {
        std::cerr << "ERROR: I/O error: " << ex.what() << std::endl;
        return 2;
    } catch (std::exception &ex) {
        std::cerr << "ERROR: Unknown  exception: " << ex.what() << std::endl;
        return 2;
    }
    return 0;
#endif
}

