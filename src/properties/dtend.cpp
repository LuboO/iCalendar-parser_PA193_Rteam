#include "dtend.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string DTEnd::NAME = "DTEND";

void DTEnd::print(std::ostream &out) const{
    out << NAME;
    for(auto &i : tzidParam) i.print(out);
    for(auto &i : valueParam) i.print(out);
    out << ":" ;
    value.print(out);
    out << "\r\n";
}

DTEnd DTEnd::parse(const core::WithPos<core::GenericProperty> &generic) {
	if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty " + NAME + " property");

    DTEnd dtend;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Tzid_param::NAME) {
            if(!dtend.tzidParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Tzid_param::NAME + " parameter can't occurr multiple times");
            dtend.tzidParam.push_back(parameters::Tzid_param::parse(i));

        } else if (i->getName().value() == parameters::Value::NAME){
            if(!dtend.valueParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Value::NAME+ " parameter can't occurr multiple times");
            dtend.valueParam.push_back(parameters::Value::parse(i));
        }else {
            throw ParserException(i.pos() , "invalid " + NAME + " property parameter");
        }
    }
    auto &value = generic->getValue();
    bool justDate;
    if(dtend.valueParam.size()==0) justDate = false;
    else if(dtend.valueParam[0].getValue() == "DATE") justDate = true;
    else if (dtend.valueParam[0].getValue() == "DATE-TIME") justDate = false;
    else throw ParserException(generic.pos() , "invalid " + NAME + " VALUE parameter can be only DATE or DATE-TIME");

    dtend.value = std::move(data::DateTime::parse(value.pos(), value->begin(), value->end(),justDate));


    return dtend;
}

} // namespace properties
} // namespace ical

