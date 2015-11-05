#include "core/genericparser.h"
#include "core/charset.h"

#include "components/vcalendar.h"
#include "parserexception.h"

#include <iostream>

using namespace std;
using namespace ical::core;

static const CharSet x = CharSet('x', 'z');

int main()
{
    // Testing stream
    std::stringstream s;
    s << "BEGIN:VCALENDAR\r\n";
    s << "VERSION;UID=:2.0\r\n";
    s << "PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n";
    s << "BEGIN:VEVENT\r\n";
    s << "UID:uid1@example.com\r\n";
    s << "DTSTAMP:19970714T170000Z\r\n";
    s << "ORGANIZER;CN=John Doe:MAILTO:john.doe@example.com\r\n";
    s << "DTSTART:19970714T170000Z\r\n";
    s << "DTEND:19970715T035959Z\r\n";
    s << "SUMMARY:Bastille Day Party\r\n";
    s << "END:VEVENT\r\n";
    s << "END:VCALENDAR\r\n";
    std::string test = s.str();

    std::vector<WithPos<GenericComponent>> comps;

    try {
        comps = GenericParser::parseStream(test.begin(), test.end());
        if(comps.size() > 1) {
            return -1; //wtf
        }
        ical::components::VCalendar root;
        root = ical::components::VCalendar::parse(comps[0]);
    } catch (ical::ParserException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    }

    return 0;
}

