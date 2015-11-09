#include "partstat.h"

namespace ical {
namespace parameters {

const std::string PartStat::NAME = "PARTSTAT";

void PartStat::print(std::ostream &out) const {
    out << ";" << NAME << "=" << value;
}

PartStat PartStat::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid " + NAME + " parameter name");
    std::string status = generic->getValue().value();
    if(status.empty())
        throw ParserException(generic.pos() , "empty parameter");

    /* Other values are not allowed */
    if(status != "NEEDS-ACTION" && status != "ACCEPTED" && status != "DECLINED" &&
       status != "TENTATIVE" && status != "DELEGATED" && status != "COMPLETED" &&
       status != "IN-PROCESS")
        throw ParserException(generic->getValue().pos() , "invalid value in " + NAME + " parameter");
    PartStat partStat;
    partStat.value = status;
    return partStat;
}

} // namespace parameters
} // namespace ical

