#include "due.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Due::NAME = "DUE";

void Due::print(std::ostream &out) const{
    out << "DUE";
    for(auto &i : tzidParam) i.print(out);
    for(auto &i : valueParam) i.print(out);
    out << ":" ;
    value.print(out);
    out << "\r\n";
}

Due Due::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty DUE property");

    Due due;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "TZID") {
            if(!due.tzidParam.empty())
                throw ParserException(i.pos() ,
                                      "TZID parameter can't occurr multiple times");
            due.tzidParam.push_back(parameters::Tzid_param::parse(i));

        } else if (i->getName().value() == "VALUE"){
            if(!due.valueParam.empty())
                throw ParserException(i.pos() ,
                                      "VALUE parameter can't occurr multiple times");
            due.valueParam.push_back(parameters::Value::parse(i));
        }else {
            throw ParserException(i.pos() , "invalid DUED property parameter");
        }
    }
    auto &value = generic->getValue();
    bool justDate;
    if(due.valueParam.size()==0) justDate = false;
    else if(due.valueParam[0].getValue() == "DATE") justDate = true;
    else if (due.valueParam[0].getValue() == "DATE-TIME") justDate = false;
    else throw ParserException(generic.pos() , "invalid DUE  VALUE parameter can be only DATE or DATE-TIME");

    due.value = std::move(data::DateTime::parse(value.pos(), value->begin(), value->end(),justDate));

    return due;
}

} // namespace properties
} // namespace ical

