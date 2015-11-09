#include "recurrenceid.h"

namespace ical {
namespace properties {

void RecurrenceId::print(std::ostream &out) const {
    out << "RECURRENCE-ID";
    for(auto &i : valueParam) i.print(out);
    for(auto &i : tzidParam) i.print(out);
    for(auto &i : rangeParam) i.print(out);

    out << ":";
    if(valueParam.empty()) {
        dateTimeValue.print(out);
    } else {
        if(valueParam.at(0).getValue() == "DATE-TIME") {
            dateTimeValue.print(out);
        } else {
            dateValue.print(out);
        }
    }
    out << "\r\n";
}

RecurrenceId RecurrenceId::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "RECURRENCE-ID")
        throw ParserException(generic.pos() , "invalid name in RECURRENCE-ID property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    RecurrenceId rid;

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == "VALUE") {
            rid.valueParam.push_back(parameters::Value::parse(i));
        } else if (i->getName().value() == "TZID") {
            rid.tzidParam.push_back(parameters::Tzid_param::parse(i));
        } else if (i->getName().value() == "RANGE") {
            rid.rangeParam.push_back(parameters::Range::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid parameter in RECCURENCE-ID property");
        }
    }

    /* Parameter can occur at most once */
    if(rid.valueParam.size() > 1)
        throw ParserException(generic.pos() , "VALUE parameter can't occurr multiple times");
    if(rid.tzidParam.size() > 1)
        throw ParserException(generic.pos() , "TZID parameter can't occurr multiple times");
    if(rid.rangeParam.size() > 1)
        throw ParserException(generic.pos() , "RANGE parameter can't occurr multiple times");

    /* Value parameter can contain only DATE-TIME/DATE */
    /* Property value is set accordingly, default is DATE-TIME */
    bool isOnlyDate = false;
    if (!rid.valueParam.empty()) {
        if (rid.valueParam.at(0).getValue() == "DATE") {
            isOnlyDate = true;
        } else if (rid.valueParam.at(0).getValue() != "DATE-TIME") {
            throw ParserException(generic.pos() , "only DATE-TIME and DATE values "
                                                  "are allowed in VALUE parameter");
        }
    }

    std::string propValue = generic->getValue().value();
    if(!isOnlyDate) {
        rid.dateTimeValue = core::ValueParser::parseDateTime(generic->getValue().pos() ,
                                                             propValue.begin() ,
                                                             propValue.end());
    } else {
        rid.dateValue = core::ValueParser::parseDate(generic->getValue().pos() ,
                                                     propValue.begin() ,
                                                     propValue.end());
    }
    return rid;
}

} // namespace properties
} // namespace ical

