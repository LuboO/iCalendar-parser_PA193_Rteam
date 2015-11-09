#include "properties/rdate.h"

#include "parameters/value.h"

#include "core/valueparser.h"

namespace ical {
namespace properties {

void RDate::print(std::ostream &out) const
{
    if (dts.empty() && periods.empty()) {
        return;
    }

    out << "RDATE";
    for (auto &t : tzid) {
        t.print(out);
    }
    if (!dts.empty()) {
        /* DATE-TIME is default */
        if (!dts.front().hasTime()) {
            out << ";VALUE=DATE";
        }
        out << ":";
        for (std::size_t i = 0; i < dts.size(); i++) {
            if (i != 0) {
                out << ",";
            }
            dts[i].print(out);
        }
    } else {
        out << ";VALUE=PERIOD";
        out << ":";
        for (std::size_t i = 0; i < periods.size(); i++) {
            if (i != 0) {
                out << ",";
            }
            periods[i].print(out);
        }
    }
}

RDate RDate::parse(const core::WithPos<core::GenericProperty> &generic)
{
    bool isPeriod = false;
    bool isOnlyDate = false;

    bool valueParamSeen = false;
    std::vector<parameters::Tzid_param> tzid;
    for (auto &param : generic->getParameters()) {
        if (param->getName().value() == "VALUE") {
            if (valueParamSeen) {
                throw ParserException(param.pos() , "The VALUE parameter cannot occur multiple times!");
            }

            auto valueParam = std::move(parameters::Value::parse(param));
            if (valueParam.getValue() == "DATE") {
                isOnlyDate = true;
            } else if (valueParam.getValue() == "PERIOD") {
                isPeriod = true;
            } else if (valueParam.getValue() != "DATE-TIME") {
                throw ParserException(param.pos(),
                                      "The value of the VALUE parameter "
                                      "must be one of 'DATE', 'DATE-TIME' "
                                      "or 'PERIOD'!");
            }
            valueParamSeen = true;
        } else if (param->getName().value() == "TZID") {
            if (!tzid.empty()) {
                throw ParserException(param.pos(), "The TZID parameter cannot occur multiple times!");
            }
            tzid.emplace_back(std::move(parameters::Tzid_param::parse(param)));
        } else {
            throw ParserException(param.pos() , "Invalid parameter on RDATE!");
        }
    }

    auto &value = generic->getValue();

    if (isPeriod) {
        std::vector<data::Period> values;
        values = std::move(core::ValueParser::parseDelimited(
                               value.pos(), value->begin(), value->end(),
                               data::Period::parse, ','));
        return { std::move(values), std::move(tzid) };
    } else {
        std::vector<data::DateTime> values;
        if (isOnlyDate) {
            auto dates = std::move(core::ValueParser::parseDelimited(
                                       value.pos(), value->begin(), value->end(),
                                       data::Date::parse, ','));
            values = std::vector<data::DateTime>(dates.begin(), dates.end());
        } else {
            values = std::move(core::ValueParser::parseDelimited(
                                   value.pos(), value->begin(), value->end(),
                                   data::DateTime::parse, ','));
        }
        return { std::move(values), std::move(tzid) };
    }
}

} // namespace properties
} // namespace ical

