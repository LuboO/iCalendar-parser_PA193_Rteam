#include "properties/trigger.h"

#include "parameters/value.h"

namespace ical {
namespace properties {

void Trigger::print(std::ostream &out) const
{
    out << "TRIGGER";
    if (!absolute) {
        /* VALUE=DURATION is default */
        relation.print(out);
        out << ":";
        duration.print(out);
    } else {
        out << "VALUE=DATE-TIME:";
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
        if (param->getName().value() == "VALUE") {
            if (valueParamSeen) {
                throw ParserException(param.pos() , "The VALUE parameter cannot occur multiple times!");
            }

            auto valueParam = std::move(parameters::Value::parse(param));
            if (valueParam.getValue() == "DATE-TIME") {
                isAbsolute = true;
            } else if (valueParam.getValue() != "DURATION") {
                throw ParserException(param.pos(),
                                      "The value of the VALUE parameter "
                                      "must be one of 'DATE', 'DATE-TIME' "
                                      "or 'PERIOD'!");
            }
            valueParamSeen = true;
        } else if (param->getName().value() == "RELATED") {
            if (relatedParamSeen) {
                throw ParserException(param.pos(), "The RELATED parameter cannot occur multiple times!");
            }
            relation = std::move(parameters::Related::parse(param));
        }
    }

    if (isAbsolute && relatedParamSeen) {
        throw ParserException(generic.pos(),
                              "The RELATED parameter cannot occur in "
                              "an absolute TRIGGER property!");
    }

    auto &value = generic->getValue();

    if (!isAbsolute) {
        return {
            std::move(data::Duration::parse(
                          value.pos(), value->begin(), value->end())),
            std::move(relation)
        };
    } else {
        auto dt = std::move(data::DateTime::parse(
                                value.pos(), value->begin(), value->end()));
        if (dt.getTime().isLocal()) {
            throw ParserException(value.pos(), "The value of the TRIGGER property must be in the UTC format!");
        }
        return { std::move(dt) };
    }
}

} // namespace properties
} // namespace ical

