#include "freebusy.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Freebusy::NAME = "FREEBUSY";

void Freebusy::print(std::ostream &out) const{
    out << "FREEBUSY";
    for(auto &i : fbtypeParam) i.print(out);
    out << ":";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i != 0) {
            out << ",";
        }
        values[i].print(out);
    }
    out << "\r\n";
}

Freebusy Freebusy::parse(const core::WithPos<core::GenericProperty> &generic) {
    auto &value = generic->getValue();

    Freebusy freebusy;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "FBTYPE") {
            if(!freebusy.fbtypeParam.empty())
                throw ParserException(i.pos() ,
                                      "FREEBUSY parameter can't occurr multiple times");
            freebusy.fbtypeParam.push_back(parameters::FBType::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid FREEBUSY property parameter");
        }
    }

    freebusy.values = std::move(core::ValueParser::parseDelimited(
                                    value.pos(), value->begin(), value->end(),
                                    data::Period::parse, ','));

    return freebusy;
}

} // namespace properties
} // namespace ical

