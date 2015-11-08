#include "percentcomplete.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

void PercentComplete::print(std::ostream &out) const {
    out << "PERCENT-COMPLETE:" << value << "\r\n";
}

PercentComplete PercentComplete::parse(const core::WithPos<core::GenericProperty> &generic) {
    if (!generic->getParameters().empty()) {
        throw ParserException(generic.pos(), "The PERCENT-COMPLETE property must have no parameters!");
    }

    auto &value = generic->getValue();
    PercentComplete perc;
    perc.value = std::move(core::ValueParser::parseInteger(value.pos(), value->begin(), value->end()));
    return perc;
}

} // namespace properties
} // namespace ical

