#include "core/genericparser.h"
#include "core/charset.h"

#include "components/vcalendar.h"
#include "parserexception.h"

#include <iostream>

using namespace ical;

static const core::CharSet x = core::CharSet('x', 'z');

int main()
{
    // Testing stream
    std::stringstream s;
    s << "BEGIN:VCALENDAR\r\n";
    s << "VERSION:2.0\r\n";
    s << "PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n";
    s << "BEGIN:VEVENT\r\n";
    s << "UID:uid1@example.com\r\n";
    s << "DTSTAMP:19970714T170000Z\r\n";
    s << "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n";
    s << "DTSTART:19970714T170000Z\r\n";
    s << "DTEND:19970715T035959Z\r\n";
    s << "SUMMARY:Bastille Day Party\r\n";
    s << "END:VEVENT\r\n";
    s << "BEGIN:VEVENT\r\n";
    s << "DTSTART:19970714T170000Z\r\n";
    s << "UID:uid1@example.com\r\n";
    s << "DTSTAMP:19970714T170000Z\r\n";
    s << "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n";
    s << "DTEND:19970715T035959Z\r\n";
    s << "SUMMARY:Bastille Day Party\r\n";
    s << "END:VEVENT\r\n";
    s << "END:VCALENDAR\r\n";
    // Another one
    s << "BEGIN:VCALENDAR\r\n";
    s << "VERSION:2.0\r\n";
    s << "PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n";
    s << "BEGIN:VEVENT\r\n";
    s << "UID:uid1@example.com\r\n";
    s << "DTSTAMP:19970714T170000Z\r\n";
    s << "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n";
    s << "DTSTART:19970714T170000Z\r\n";
    s << "DTEND:19970715T035959Z\r\n";
    s << "SUMMARY:Second Bastille Day Party\r\n";
    s << "END:VEVENT\r\n";
    s << "END:VCALENDAR\r\n";
    std::string test = s.str();
    std::vector<core::WithPos<core::GenericComponent>> vCalObjects;

    try {
        vCalObjects = core::GenericParser::parseStream(test.begin(), test.end());
    } catch (ParserException ex) {
        std::cout << "[ERROR] parsing: " << ex.what() << std::endl;
        return -1;
    }

    for(auto &i : vCalObjects) {
        try {
            components::VCalendar vCalRoot;
            vCalRoot = components::VCalendar::parse(i);
            std::cout << "iCalendar is valid." << std::endl << std::endl;
            vCalRoot.print(std::cout);
            std::cout << std::endl << std::endl;
        } catch (ParserException ex) {
            std::cout << "[ERROR] validation: " << ex.what()
                      << std::endl << std::endl << std::endl;
        }
    }
    return 0;
}

