#include "properties/exdate.h"

#include "parameters/value.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

const std::string ExDate::NAME = "EXDATE";

void ExDate::print(std::ostream &out) const
{
    if (values.size() == 0) {
        return;
    }
    out << NAME;
    for (auto &t : tzid) {
        t.print(out);
    }
    /* DATE-TIME is default */
    if (!values.front().hasTime()) {
        out << ";" << parameters::Value::NAME << "=DATE";
    }
    out << ":";
    for (std::size_t i = 0; i < values.size(); i++) {
        if (i != 0) {
            out << ",";
        }
        values[i].print(out);
    }
    out << "\r\n";
}

ExDate ExDate::parse(const core::WithPos<core::GenericProperty> &generic)
{
    bool isOnlyDate = false;

    bool valueParamSeen = false;
    std::vector<parameters::Tzid_param> tzid;
    for (auto &param : generic->getParameters()) {
        if (param->getName().value() == parameters::Value::NAME) {
            if (valueParamSeen) {
                throw ParserException(param.pos() , "The " + parameters::Value::NAME + " parameter cannot occur multiple times!");
            }
            parameters::Value valueParam = std::move(parameters::Value::parse(param));
            if (valueParam.getValue() == "DATE") {
                isOnlyDate = true;
            } else if (valueParam.getValue() != "DATE-TIME") {
                throw ParserException(param.pos(),
                                      "The value of the " + parameters::Value::NAME + " parameter "
                                      "must be one of 'DATE' or 'DATE-TIME'!");
            }
            valueParamSeen = true;
        } else if (param->getName().value() == parameters::Tzid_param::NAME) {
            if (!tzid.empty()) {
                throw ParserException(param.pos() , "The " + parameters::Tzid_param::NAME + " parameter cannot occur multiple times!");
            }
            tzid.emplace_back(std::move(parameters::Tzid_param::parse(param)));
        } else {
            throw ParserException(param.pos() , "Invalid parameter on EXDATE!");
        }
    }

    auto &value = generic->getValue();

    std::vector<data::DateTime> values;
    if (isOnlyDate) {
        auto dates = std::move(core::ValueParser::parseDelimited(
                                   value.pos(), value->begin(), value->end(),
                                   data::DateTime::parse, ','));
        values = std::vector<data::DateTime>(dates.begin(), dates.end());
    } else {
        values = std::move(core::ValueParser::parseDelimited(
                               value.pos(), value->begin(), value->end(),
                               data::DateTime::parse, ','));
    }
    return { std::move(values), std::move(tzid) };
}

} // namespace properties
} // namespace ical

