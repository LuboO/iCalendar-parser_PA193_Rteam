#include "contact.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void Contact::print(std::ostream &out) const {
    out << "CONTACT";
    for(auto &i : altRepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << core::ValueParser::encodeText(value) << "\r\n";
}

Contact Contact::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "CONTACT")
        throw ParserException(generic.pos() , "invalid name in CONTACT property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();

    Contact contact;
    contact.value = std::move(core::ValueParser::parseText(
                                  value.pos(), value->begin(), value->end()));

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "ALTREP") {
            if(!contact.altRepParam.empty())
                throw ParserException(i.pos() ,
                                      "ALTREP parameter can't occurr multiple times");
            contact.altRepParam.push_back(parameters::AltRep::parse(i));

        } else if(i->getName().value() == "LANGUAGE") {
            if(!contact.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            contact.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid CONTACT property parameter");
        }
    }
    return contact;
}

} // namespace properties
} // namespace ical

