#include "properties/trigger.h"

#include "parameters/value.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string Trigger::NAME = "TRIGGER";

void Trigger::print(std::ostream &out) const
{
    out << NAME;
    if (!absolute) {
        /* VALUE=DURATION is default */
        relation.print(out);
        out << ":";
        duration.print(out);
    } else {
        out << parameters::Value::NAME + "=DATE-TIME:";
        start.print(out);
    }
}

Trigger Trigger::parse(const core::WithPos<core::GenericProperty> &generic)
{
    bool isAbsolute = false;
    parameters::Related relation;

    bool valueParamSeen = false;
    bool relatedParamSeen = false;
    for (auto &param : generic->getParameters()) {
        if (param->getName().value() == parameters::Value::NAME) {
            if (valueParamSeen) {
                throw ParserException(param.pos() , "The " + parameters::Value::NAME + " parameter cannot occur multiple times!");
            }

            auto valueParam = std::move(parameters::Value::parse(param));
            if (valueParam.getValue() == "DATE-TIME") {
                isAbsolute = true;
            } else if (valueParam.getValue() != "DURATION") {
                throw ParserException(param.pos(),
                                      "The value of the " + parameters::Value::NAME + " parameter "
                                      "must be one of 'DATE', 'DATE-TIME' "
                                      "or 'PERIOD'!");
            }
            valueParamSeen = true;
        } else if (param->getName().value() == parameters::Related::NAME) {
            if (relatedParamSeen) {
                throw ParserException(param.pos(), "The " + parameters::Related::NAME + " parameter cannot occur multiple times!");
            }
            relation = std::move(parameters::Related::parse(param));
        }
    }

    if (isAbsolute && relatedParamSeen) {
        throw ParserException(generic.pos(),
                              "The " + parameters::Related::NAME + " parameter cannot occur in "
                              "an absolute " + NAME + " property!");
    }

    auto &value = generic->getValue();

    if (!isAbsolute) {
        return {
            std::move(core::ValueParser::parseDuration(value.pos(), value->begin(), value->end())),
            std::move(relation)
        };
    } else {
        auto dt = std::move(core::ValueParser::parseDateTime(value.pos(), value->begin(), value->end()));
        if (dt.getTime().isLocal()) {
            throw ParserException(value.pos(), "The value of the " + NAME + " property must be in the UTC format!");
        }
        return { std::move(dt) };
    }
}

} // namespace properties
} // namespace ical

