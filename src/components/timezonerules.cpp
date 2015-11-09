#include "components/timezonerules.h"

namespace ical {
namespace components {

void TimeZoneRules::print(std::ostream &out, const char *name) const
{
    out << "BEGIN:" << name << "\r\n";
    start.print(out);
    from.print(out);
    to.print(out);
    for (auto &rule : rrules) {
        rule.print(out);
    }
    for (auto &rdate : rdates) {
        rdate.print(out);
    }
    for (auto &name : names) {
        name.print(out);
    }
    for (auto &comment : comments) {
        comment.print(out);
    }
    out << "END:" << name << "\r\n";
}

TimeZoneRules TimeZoneRules::parse(const core::WithPos<core::GenericComponent> &generic)
{
    TimeZoneRules res;

    bool startSeen = false;
    bool fromSeen = false;
    bool toSeen = false;
    for (auto &prop : generic->getProperties()) {
        auto &name = prop->getName();
        if (*name == "DTSTART") {
            if (startSeen) {
                throw ParserException(
                            prop.pos(),
                            "This component must not contain multiple "
                            "DTSTART properties!");
            }

            res.start = std::move(properties::Dtstart::parse(prop));

            if (!res.start.getValue().hasTime() ||
                    !res.start.getValue().getTime().isLocal()) {
                throw ParserException(
                            prop.pos(),
                            "The value of the DTSTART property in this "
                            "component must be a date-time with the time in "
                            "the local format!");
            }

            startSeen = true;
        } else if (*name == "TZOFFSETFROM") {
            if (fromSeen) {
                throw ParserException(
                            prop.pos(),
                            "This component must not contain multiple "
                            "TZOFFSETFROM properties!");
            }

            res.from = std::move(properties::TZOffsetFrom::parse(prop));

            fromSeen = true;
        } else if (*name == "TZOFFSETTO") {
            if (toSeen) {
                throw ParserException(
                            prop.pos(),
                            "This component must not contain multiple "
                            "TZOFFSETTO properties!");
            }

            res.to = std::move(properties::TZOffsetTo::parse(prop));

            toSeen = true;
        } else if (*name == "RRULE") {
            properties::RRule rrule = std::move(properties::RRule::parse(prop));

            auto &value = rrule.getValue();
            if (value.isLimited()) {
                if (value.isLimitedByCount()) {
                    throw ParserException(
                                prop.pos(),
                                "The RRULE property inside VTIMEZONE can "
                                "only be limited by an end date!");
                }
                if (!value.getEndDate().hasTime()) {
                    throw ParserException(
                                prop.pos(),
                                "The end date of the RRULE property inside "
                                "VTIMEZONE must be a date-time value!");
                }
                if (!value.getEndDate().getTime().isLocal()) {
                    throw ParserException(
                                prop.pos(),
                                "The end date of the RRULE property inside "
                                "VTIMEZONE must be in the UTC format!");
                }
            }

            res.rrules.emplace_back(std::move(rrule));
        } else if (*name == "COMMENT") {
            res.comments.emplace_back(std::move(properties::Comment::parse(prop)));
        } else if (*name == "RDATE") {
            properties::RDate rdate = std::move(properties::RDate::parse(prop));
            if (rdate.hasPeriods()) {
                throw ParserException(
                            prop.pos(),
                            "The RDATE property inside VTIMEZONE can "
                            "only have date-time values!");
            }
            for (auto &dt : rdate.getDateTimes()) {
                if (!dt.hasTime()) {
                    throw ParserException(
                                prop.pos(),
                                "The RDATE property inside VTIMEZONE can "
                                "only have date-time values!");
                }
                if (!dt.getTime().isLocal()) {
                    throw ParserException(
                                prop.pos(),
                                "The values of the RDATE property inside "
                                "VTIMEZONE must be in local time format!");
                }
            }
            res.rdates.emplace_back(std::move(rdate));
        } else if (*name == "TZNAME") {
            res.names.emplace_back(std::move(properties::TZName::parse(prop)));
        } else {
            throw ParserException(prop.pos(), "Invalid property!");
        }
    }

    if (!startSeen) {
        throw ParserException(generic.pos(), "The DTSTART property is required!");
    }
    if (!fromSeen) {
        throw ParserException(generic.pos(), "The TZOFFSETFROM property is required!");
    }
    if (!toSeen) {
        throw ParserException(generic.pos(), "The TZOFFSETTO property is required!");
    }

    if (!generic->getSubcomponents().empty()) {
        throw ParserException(generic.pos(), "The component cannot have subcomponents!");
    }
    return res;
}

} // namespace components
} // namespace ical

