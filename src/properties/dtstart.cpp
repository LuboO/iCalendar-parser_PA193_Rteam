#include "dtstart.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string DTStart::NAME = "DTSTART";

void DTStart::print(std::ostream &out) const{
    out << NAME;
    for(auto &i : tzidParam) i.print(out);
    for(auto &i : valueParam) i.print(out);
    out << ":" ;
    value.print(out);
    out << "\r\n";
}

DTStart DTStart::parse(const core::WithPos<core::GenericProperty> &generic) {
	if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty " + NAME + " property");

    DTStart dtstart;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Tzid_param::NAME) {
            if(!dtstart.tzidParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Tzid_param::NAME + " parameter can't occurr multiple times");
            dtstart.tzidParam.push_back(parameters::Tzid_param::parse(i));

        } else if (i->getName().value() == parameters::Value::NAME){
            if(!dtstart.valueParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Value::NAME + " parameter can't occurr multiple times");
            dtstart.valueParam.push_back(parameters::Value::parse(i));
        }else {
            throw ParserException(i.pos() , "invalid " + NAME + " property parameter");
        }
    }
    auto &value = generic->getValue();
    bool justDate;
    if(dtstart.valueParam.size()==0) justDate = false;
    else if(dtstart.valueParam[0].getValue() == "DATE") justDate = true;
    else if (dtstart.valueParam[0].getValue() == "DATE-TIME") justDate = false;
    else throw ParserException(generic.pos() , "invalid " + NAME + " VALUE parameter can be only DATE or DATE-TIME");

    dtstart.value = std::move(
                data::DateTime::parse(
                    value.pos(), value->begin(), value->end(),justDate));

    return dtstart;
}

} // namespace properties
} // namespace ical

