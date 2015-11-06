#include "properties/dtstamp.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void DTStamp::print(std::ostream &out) const
{
    out << "DTSTAMP:";
    value.print(out);
    out << "\r\n";
}

DTStamp DTStamp::parse(const core::WithPos<core::GenericProperty> &generic)
{
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The DTSTAMP property must have no parameters!");
    }

    auto &value = generic->getValue();
    auto dt = std::move(core::ValueParser::parseDateTime(
                            value.pos(), value->begin(), value->end()));
    if (dt.getTime().isLocal()) {
        throw ParserException(value.pos(), "The value of the DTSTAMP property must be in the UTC format!");
    }
    return { std::move(dt) };
}

} // namespace properties
} // namespace ical

