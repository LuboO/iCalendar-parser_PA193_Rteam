#include "properties/recurrenceid.h"

namespace ical {
namespace properties {

const std::string RecurrenceId::NAME = "RECURRENCE-ID";

void RecurrenceId::print(std::ostream &out) const {
    out << NAME;
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
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    RecurrenceId rid;

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Value::NAME) {
            rid.valueParam.push_back(parameters::Value::parse(i));
        } else if (i->getName().value() == parameters::Tzid_param::NAME) {
            rid.tzidParam.push_back(parameters::Tzid_param::parse(i));
        } else if (i->getName().value() == parameters::Range::NAME) {
            rid.rangeParam.push_back(parameters::Range::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid parameter in " + NAME + " property");
        }
    }

    /* Parameter can occur at most once */
    if(rid.valueParam.size() > 1)
        throw ParserException(generic.pos() , parameters::Value::NAME + " parameter can't occurr multiple times");
    if(rid.tzidParam.size() > 1)
        throw ParserException(generic.pos() , parameters::Tzid_param::NAME + " parameter can't occurr multiple times");
    if(rid.rangeParam.size() > 1)
        throw ParserException(generic.pos() , parameters::Range::NAME + " parameter can't occurr multiple times");

    /* Value parameter can contain only DATE-TIME/DATE */
    /* Property value is set accordingly, default is DATE-TIME */
    bool isOnlyDate = false;
    if (!rid.valueParam.empty()) {
        if (rid.valueParam.at(0).getValue() == "DATE") {
            isOnlyDate = true;
        } else if (rid.valueParam.at(0).getValue() != "DATE-TIME") {
            throw ParserException(generic.pos() , "only DATE-TIME and DATE values "
                                                  "are allowed in " + parameters::Value::NAME + " parameter");
        }
    }

    auto &propValue = generic->getValue();
    if(!isOnlyDate) {
        rid.dateTimeValue = data::DateTime::parse(
                    propValue.pos(), propValue->begin(), propValue->end());
    } else {
        rid.dateValue = data::Date::parse(
                    propValue.pos(), propValue->begin(), propValue->end());
    }
    return rid;
}

} // namespace properties
} // namespace ical

