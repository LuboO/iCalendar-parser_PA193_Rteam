#include "properties/uid.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Uid::NAME = "UID";

void Uid::print(std::ostream &out) const {
    out << NAME << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

Uid Uid::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name id " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    if(!generic->getParameters().empty())
        throw ParserException(generic.pos() , "invalid parameter in " + NAME + " property");


    auto &value = generic->getValue();

    /* Uniqueness of this value is checked elsewhere */
    Uid uid;
    uid.value = std::move(core::ValueParser::parseText(
                              value.pos(), value->begin(), value->end()));
    return uid;
}

} // namespace properties
} // namespace ical

