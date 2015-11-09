#include "dtstart.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

void Dtstart::print(std::ostream &out) const{
    out << "DTSTART";
    for(auto &i : tzidParam) i.print(out);
    for(auto &i : valueParam) i.print(out);
    out << ":" ;
    value.print(out);
    out << "\r\n";
}

Dtstart Dtstart::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty DTSTART property");

    Dtstart dtstart;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "TZID") {
            if(!dtstart.tzidParam.empty())
                throw ParserException(i.pos() ,
                                      "TZID parameter can't occurr multiple times");
            dtstart.tzidParam.push_back(parameters::Tzid_param::parse(i));

        } else if (i->getName().value() == "VALUE"){
            if(!dtstart.valueParam.empty())
                throw ParserException(i.pos() ,
                                      "VALUE parameter can't occurr multiple times");
            dtstart.valueParam.push_back(parameters::Value::parse(i));
        }else {
            throw ParserException(i.pos() , "invalid DTSTART property parameter");
        }
    }
    auto &value = generic->getValue();
    bool justDate;
    if(dtstart.valueParam.size()==0) justDate = false;
    else if(dtstart.valueParam[0].getValue() == "DATE") justDate = true;
    else if (dtstart.valueParam[0].getValue() == "DATE-TIME") justDate = false;
    else throw ParserException(generic.pos() , "invalid DTSTART  VALUE parameter can be only DATE or DATE-TIME");

    dtstart.value = std::move(data::DateTime::parse(value.pos(), value->begin(), value->end(),justDate));

    return dtstart;
}

} // namespace properties
} // namespace ical

