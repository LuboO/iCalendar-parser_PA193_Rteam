#include "requeststatus.h"

#include "core/valueparser.h"

#include <regex>

namespace ical {
namespace properties {

const std::string RequestStatus::NAME = "REQUEST-STATUS";

void RequestStatus::print(std::ostream &out) const {
    out << NAME;
    for(auto &i :languageParam) i.print(out);
    out << ":"
        << statCode << ";"
        << core::ValueParser::encodeText(statDesc);
    if (!data.empty()) {
        out << ";" << core::ValueParser::encodeText(data);
    }
    out << "\r\n";
}

RequestStatus RequestStatus::parse(const core::WithPos<core::GenericProperty> &generic) {
    if(generic->getName().value() != NAME)
        throw ParserException(generic.pos() , "invalid name in " + NAME + " property");
    if(generic->getValue()->empty())
        throw ParserException(generic.pos() , "empty property");

    auto &value = generic->getValue();
    auto components = std::move(core::ValueParser::parseDelimitedEscaped(
                                    value.pos(), value->begin(), value->end(),
                                    core::ValueParser::parseText, ';'));
    if (components.size() < 2) {
        throw ParserException(value.pos() , "Too few value components!");
    }
    if (components.size() > 3) {
        throw ParserException(value.pos() , "Too many value components!");
    }

    RequestStatus status;
    status.statCode = components[0];
    status.statCode = components[1];
    status.data = components.size() > 2 ? components[2] : std::string();

	static const std::regex RE_STATCODE { "[0-9]+(\\.[0-9]+){1,2}" };
    if (!std::regex_match(status.statCode, RE_STATCODE)) {
        throw ParserException(value.pos() , "Invalid request status code!");
    }

    for(const auto &i : generic->getParameters()) {
        if(i->getName().value() == parameters::Language::NAME) {
            if(!status.languageParam.empty())
                throw ParserException(i.pos() , parameters::Language::NAME + " parameter can't occurr multiple times");
            status.languageParam.push_back(parameters::Language::parse(i));

        } else {
            throw ParserException(i.pos() , "invalid parameter in " + NAME + " property");
        }
    }
    return status;
}

} // namespace properties
} // namespace ical

