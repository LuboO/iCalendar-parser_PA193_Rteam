#include "core/genericparsertemplate.h"

namespace ical {
namespace core {

/* See: https://tools.ietf.org/html/rfc5234#appendix-B.1 */
const CharSet GenericParserTemplate::ALPHANUMERIC =
        CharSet('A', 'Z') | CharSet('a', 'z') | CharSet('0', '9');
const CharSet GenericParserTemplate::WSP = CharSet(' ') | CharSet('\t');
const CharSet GenericParserTemplate::CONTROL =
        (CharSet('\0', '\x1f') | CharSet('\x7f')) & ~CharSet('\t');

/* See: https://tools.ietf.org/html/rfc5545#section-3.1 */
const CharSet GenericParserTemplate::IANA_TOKEN = ALPHANUMERIC | CharSet('-');
const CharSet GenericParserTemplate::QSAFE_CHAR = ~(CONTROL | CharSet('"'));
const CharSet GenericParserTemplate::SAFE_CHAR =
        ~(CONTROL | CharSet('"') | CharSet(';') | CharSet(':') | CharSet(','));
const CharSet GenericParserTemplate::VALUE_CHAR = ~CONTROL;

} // namespace core
} // namespace ical

