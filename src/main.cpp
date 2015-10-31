#include "core/genericparser.h"
#include "core/charset.h"

#include <iostream>

using namespace std;
using namespace ical::core;

static const CharSet x = CharSet('x', 'z');

int main()
{
    std::string test { "BEG\r\n IN:TEST\r\nX;Y=2:he\r\n\tllo\r\nEND:TE/ST\r\n" };
    GenericParser::parseStream(test.begin(), test.end());
    return 0;
}

