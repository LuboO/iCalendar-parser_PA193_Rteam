#include "requeststatus.h"

namespace ical {
namespace properties {

const std::string RequestStatus::NAME = "REQUEST-STATUS";

void RequestStatus::print(std::ostream &out) const {
    out << NAME;
    for(auto &i :languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

RequestStatus RequestStatus::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    RequestStatus status;
    /* Value of statcode, statdesc and extdata is not validated */
    status.value = generic->getValue().value();

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Language::NAME) {
            if(!status.languageParam.empty())
                throw ParserException(i.pos() , parameters::Language::NAME + " parameter can't occurr multiple times");
            status.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in " + NAME + " property");
        }
    }
    return status;
}

} // namespace properties
} // namespace ical

