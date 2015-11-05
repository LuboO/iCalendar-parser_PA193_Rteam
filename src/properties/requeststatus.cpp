#include "requeststatus.h"

namespace ical {
namespace properties {

void RequestStatus::print(std::ostream &out) const {
    out << "REQUEST-STATUS";
    for(auto &i :languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

RequestStatus RequestStatus::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "REQUEST-STATUS")
        throw ParserException(generic.pos() , "invalid name in REQUEST-STATUS property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    RequestStatus status;
    /* Value of statcode, statdesc and extdata is not validated */
    status.value = generic->getValue().value();

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == "LANGUAGE") {
            if(!status.languageParam.empty())
                throw ParserException(i.pos() , "LANGUAGE parameter can't occurr multiple times");
            status.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in REQUEST-STATUS property");
        }
    }
    return status;
}

} // namespace properties
} // namespace ical

