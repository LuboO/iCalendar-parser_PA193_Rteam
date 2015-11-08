#include "comment.h"

namespace ical {
namespace properties {

void Comment::print(std::ostream &out) const {
    out << "COMMENT";
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

Comment Comment::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "COMMENT")
        throw ParserException(generic.pos() , "invalid name in COMMENT property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty COMMENT property");
    Comment comment;
    comment.value = generic->getValue().value();
    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "ALTREP") {
            if(!comment.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      "ALTREP parameter can't occurr multiple times");
            comment.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == "LANGUAGE") {
            if(!comment.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            comment.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid COMMENT property parameter");
        }
    }
    return comment;
}

} // namespace properties
} // namespace ical

