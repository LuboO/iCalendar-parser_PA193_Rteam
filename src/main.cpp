#include "parser.h"

#include <iostream>

using namespace ical;

int main()
{
    // Testing stream
    std::vector<std::string> tests {
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
        "END:VCALENDAR\r\n",

        // Another one
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
    };
    for (auto &str : tests) {
        std::vector<components::VCalendar> vCalObjects;
        try {
            vCalObjects = std::move(Parser::parseString(str));
        } catch (ParserException ex) {
            std::cout << "[ERROR] parsing: " << ex.what() << std::endl;
            std::cout << std::endl << std::endl;
            continue;
        }
        std::cout << "iCalendar is valid." << std::endl << std::endl;

        for(auto &vCalRoot : vCalObjects) {
            vCalRoot.print(std::cout);
        }
        std::cout << std::endl << std::endl;
    }
    return 0;
}

