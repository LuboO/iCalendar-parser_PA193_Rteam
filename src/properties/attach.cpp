#include "properties/attach.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Attach::NAME = "ATTACH";

void Attach::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : fmttypeParam) i.print(out);
    for(auto &i : encodingParam) i.print(out);
    for(auto &i : valueParam) i.print(out);
    if (valueParam.size() > 0) {
        /* BASE64 binary data; reencode: */
        out << ":" << core::ValueParser::encodeBase64(value) << "\r\n";
    } else {
        /* just a URI: */
        out << ":" << value << "\r\n";
    }
}

Attach Attach::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    Attach attach;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::FmtType::NAME) {
            if(!attach.fmttypeParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::FmtType::NAME + " parameter can't occurr multiple times");
            attach.fmttypeParam.push_back(parameters::FmtType::parse(i));

        } else if(i->getName().value() == parameters::Encoding::NAME) {
            if(!attach.encodingParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Encoding::NAME + " parameter can't occurr multiple times");
            attach.encodingParam.push_back(parameters::Encoding::parse(i));

        } else if(i->getName().value() == parameters::Value::NAME) {
            if(!attach.valueParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Value::NAME + " parameter can't occur multiple times");
            attach.valueParam.push_back(parameters::Value::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid " + NAME + " property parameter");
        }
    }

    if (attach.encodingParam.empty() && attach.valueParam.empty())
    {
        core::ValueParser::validateUri(value.pos(), *value);
        attach.value = *value;
    }
    else if(attach.encodingParam.size()==1 && attach.valueParam.size()==1
            && attach.encodingParam[0].getValue()=="BASE64" && attach.valueParam[0].getValue()=="BINARY")
    {
        attach.value = std::move(core::ValueParser::parseBase64(
                                      value.pos(), value->begin(), value->end()));
    } else {
        throw ParserException(generic.pos() , "invalid value of parameter ENCODING or VALUE");
    }
    return attach;

}

} // namespace properties
} // namespace ical

