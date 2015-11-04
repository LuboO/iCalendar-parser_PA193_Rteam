#include "contact.h"

namespace ical {
namespace properties {

void Contact::print(std::ostream &out) const {
    out << "CONTACT";
    //for(auto &i : altrepParam) i.print(out);
    for(auto &i : languageParam) i.print(out);
    out << ":" << value << "\r\n";
}

Contact Contact::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != "CONTACT")
        throw ParserException(generic.pos() , "invalid name in CONTACT property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");
    Contact contact;
    contact.value = generic->getValue().value();
    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "ALTREP") {
            //wait for impl
        } else if(i->getName().value() == "LANGUAGE") {
            if(!contact.languageParam.empty())
                throw ParserException(i.pos() , "LANGUAGE parameter can't occurr multiple times");
            contact.languageParam.push_back(parameters::Language::parse(i));
        } else {
            throw ParserException(i.pos() , "invalid CONTACT property parameter");
        }
    }
    return contact;
}

} // namespace properties
} // namespace ical

