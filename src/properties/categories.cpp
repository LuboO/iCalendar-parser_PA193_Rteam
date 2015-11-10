#include "categories.h"
#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Categories::NAME = "CATEGORIES";

void Categories::print(std::ostream &out) const {
    out << "CATEGORIES";
    for(auto &i : languageParam) i.print(out);
    out << ":";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i != 0) {
            out << ",";
        }
        out << values[i];
    }
    out << "\r\n";
}

Categories Categories::parse(const core::WithPos<core::GenericProperty> &generic) {
    auto &value = generic->getValue();

    Categories categories;

    for(auto &i : generic->getParameters()) {
        if(i->getName().value() == "LANGUAGE") {
            if(!categories.languageParam.empty())
                throw ParserException(i.pos() ,
                                      "LANGUAGE parameter can't occurr multiple times");
            categories.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid CATEGORIES property parameter");
        }
    }

    categories.values = std::move(
                core::ValueParser::parseDelimitedEscaped(
                    value.pos(), value->begin(), value->end(),
                    core::ValueParser::parseText, ','));
    return categories;
}

} // namespace properties
} // namespace ical

