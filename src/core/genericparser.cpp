#include "core/genericparser.h"

namespace ical {
namespace core {

/* See: https://tools.ietf.org/html/rfc5234#appendix-B.1 */
const CharSet GenericParser::ALPHANUMERIC =
        CharSet('A', 'Z') | CharSet('a', 'z') | CharSet('0', '9');
const CharSet GenericParser::WSP = CharSet(' ') | CharSet('\t');
const CharSet GenericParser::CONTROL =
        (CharSet('\0', '\x1f') | CharSet('\x7f')) & ~CharSet('\t');

/* See: https://tools.ietf.org/html/rfc5545#section-3.1 */
const CharSet GenericParser::IANA_TOKEN = ALPHANUMERIC | CharSet('-');
const CharSet GenericParser::QSAFE_CHAR = ~(CONTROL | CharSet('"'));
const CharSet GenericParser::SAFE_CHAR =
        ~(CONTROL | CharSet('"') | CharSet(';') | CharSet(':') | CharSet(','));
const CharSet GenericParser::VALUE_CHAR = ~CONTROL;

std::vector<WithPos<GenericComponent>>
GenericParser::parseStream(std::istream &stream)
{
    return parseStream(std::istreambuf_iterator<char>(stream),
                       std::istreambuf_iterator<char>());
}

} // namespace core
} // namespace ical

