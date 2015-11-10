#include "properties/comment.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Comment::NAME = "COMMENT";

void Comment::print(std::ostream &out) const {
    out << NAME;
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

Comment Comment::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty " + NAME + " property");

    auto &value = generic->getValue();

    Comment comment;
    comment.value = std::move(core::ValueParser::parseText(
                                  value.pos(), value->begin(), value->end()));

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::AltRep::NAME) {
            if(!comment.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::AltRep::NAME + " parameter can't occurr multiple times");
            comment.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == parameters::Language::NAME) {
            if(!comment.languageParam.empty())
                throw ParserException(i.pos() ,
                                      parameters::Language::NAME + " parameter can't occurr multiple times");
            comment.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid " + NAME + " property parameter");
        }
    }
    return comment;
}

} // namespace properties
} // namespace ical

