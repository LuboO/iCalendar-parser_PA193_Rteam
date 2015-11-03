#include "partstat.h"

namespace ical {
namespace parameters {

void PartStat::print(std::ostream &out) const {
    out << ";PARTSTAT=" << value;
}

PartStat PartStat::parse(const core::WithPos<core::GenericPropertyParameter> &generic) {
    if(generic->getName().value() != "PARTSTAT")
        throw ParserException(generic.pos() , "invalid PARTSTAT parameter name");
    std::string status = generic->getValue().value();
    /* Other values are not allowed */
    if(status != "NEEDS-ACTION" &&
       status != "ACCEPTED" &&
       status != "DECLINED" &&
       status != "TENTATIVE" &&
       status != "DELEGATED" &&
       status != "COMPLETED" &&
       status != "IN-PROCESS")
        throw ParserException(generic->getValue().pos() , "invalid value in PARTSTAT parameter");
    PartStat partStat;
    partStat.value = status;
    return partStat;
}

} // namespace parameters
} // namespace ical

