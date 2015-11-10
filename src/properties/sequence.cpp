#include "properties/sequence.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Sequence::NAME = "SEQUENCE";

void Sequence::print(std::ostream &out) const
{
    if (seqNum == 0) {
        return;
    }

    out << NAME << ":" << seqNum << "\r\n";
}

Sequence Sequence::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The " + NAME + " property must have no parameters!");
    }

    auto &value = generic->getValue();
    return Sequence {
        core::ValueParser::parseUnsignedInteger(
                    value.pos(), value->begin(), value->end())
    };
}

} // namespace properties
} // namespace ical

