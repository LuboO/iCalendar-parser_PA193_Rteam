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
        value.print(out);
    } else {
        if(valueParam.at(0).getValue() == "DATE-TIME") {
            value.print(out);
        } else {
            value.getDate().print(out);
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

    bool justDate;
    if(rid.valueParam.empty()) justDate = false;
    else if(rid.valueParam.at(0).getValue() == "DATE") justDate = true;
    else if(rid.valueParam.at(0).getValue() == "DATE-TIME") justDate = false;
    else throw ParserException(generic.pos() , "invalid " + NAME + " property: only DATE "
                                               "or DATE-TIME can be in VALUE parameter");
    auto & value = generic->getValue();
    if(justDate) {
        rid.value = data::DateTime { data::Date::parse(value.pos(),
                                                       value->begin(),
                                                       value->end()) };
    } else {
        rid.value = data::DateTime::parse(value.pos(), value->begin(), value->end());
    }

    return rid;
}

} // namespace properties
} // namespace ical

