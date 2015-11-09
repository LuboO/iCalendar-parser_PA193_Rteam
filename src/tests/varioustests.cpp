#include "tests/varioustests.h"

#include "parser.h"

#include <vector>

namespace ical {
namespace tests {

std::vector<std::pair<bool, std::string>> VALIDATION {
    {
        false,
        "BEGIN:VCALENDAR\r\n"
        "VERSION:2.0\r\n"
        "PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
        "BEGIN:VEVENT\r\n"
        "UID:uid1@example.com\r\n"
        "DTSTAMP:19970714T170000Z\r\n"
        "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n"
        "DTSTART:19970714T170000Z\r\n"
        "DTEND:19970715T035959Z\r\n"
        "SUMMARY:Bastille Day Party\r\n"
        "END:VEVENT\r\n"
        "BEGIN:VEVENT\r\n"
        "DTSTART:19970714T170000Z\r\n"
        "UID:uid1@example.com\r\n"
        "DTSTAMP:19970714T170000Z\r\n"
        "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n"
        "DTEND:19970715T035959Z\r\n"
        "SUMMARY:Bastille Day Party\r\n"
        "END:VEVENT\r\n"
        "END:VCALENDAR\r\n"
    },
    {
        true,
        "BEGIN:VCALENDAR\r\n"
        "VERSION:2.0\r\n"
        "PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
        "BEGIN:VEVENT\r\n"
        "UID:uid1@example.com\r\n"
        "DTSTAMP:19970714T170000Z\r\n"
        "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n"
        "DTSTART:19970714T170000Z\r\n"
        "DTEND:19970715T035959Z\r\n"
        "SUMMARY:Second Bastille Day Party\r\n"
        "END:VEVENT\r\n"
        "END:VCALENDAR\r\n"
    },
};

static bool tryParseCalendar(const std::string &str)
{
    try {
        Parser::parseString(str);
        return true;
    } catch (ParserException &ex) {
        return false;
    }
}

void VariousTests::runTests(TestReporter &tr)
{
    tr.reportTestSuite("Various tests");
    for (auto &val : VALIDATION) {
        bool valid = tryParseCalendar(val.second);
        tr.registerTest("Is '" + val.second + "' valid?",
                        val.first, valid);
    }
}

} // namespace tests
} // namespace ical

