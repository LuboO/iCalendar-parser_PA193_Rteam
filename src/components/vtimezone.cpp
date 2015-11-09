#include "vtimezone.h"

namespace ical {
namespace components {

const std::string VTimeZone::NAME = "VTIMEZONE";

void VTimeZone::print(std::ostream &out) const
{
    out << "BEGIN:" << NAME << "\r\n";
    tzid.print(out);
    for (auto &lm : lastModified) {
        lm.print(out);
    }
    for (auto &url : tzUrl) {
        url.print(out);
    }
    for (auto &rules : standardRules) {
        rules.print(out, "STANDARD");
    }
    for (auto &rules : dstRules) {
        rules.print(out, "DAYLIGHT");
    }
    out << "END:" << NAME << "\r\n";
}

VTimeZone VTimeZone::parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &tzidRegistry)
{
    VTimeZone res;

    bool tzidSeen = false;
    bool lastModifiedSeen = false;
    bool tzUrlSeen = false;
    for (auto &prop : generic->getProperties()) {
        auto &name = prop->getName();
        if (*name == properties::TZId::NAME) {
            if (tzidSeen) {
                throw ParserException(
                            prop.pos(),
                            "This component must not contain multiple "
                            + properties::TZId::NAME + " properties!");
            }

            res.tzid = std::move(properties::TZId::parse(prop));
            if (!tzidRegistry.registerId(res.tzid.getValue())) {
                throw ParserException(
                            prop.pos(),
                            "The value of the TZID property must be unique for "
                            "each VTIMEZONE component!");
            }

            tzidSeen = true;
        } else if (*name ==properties::LastModified::NAME) {
            if (lastModifiedSeen) {
                throw ParserException(
                            prop.pos(),
                            "This component must not contain multiple "
                            + properties::LastModified::NAME + " properties!");
            }

            res.lastModified.emplace_back(std::move(properties::LastModified::parse(prop)));

            lastModifiedSeen = true;
        } else if (*name == properties::TZUrl::NAME) {
            if (tzUrlSeen) {
                throw ParserException(
                            prop.pos(),
                            "This component must not contain multiple "
                            + properties::TZUrl::NAME + " properties!");
            }

            res.tzUrl.emplace_back(std::move(properties::TZUrl::parse(prop)));

            tzUrlSeen = true;
        } else {
            throw ParserException(prop.pos(), "Invalid property!");
        }
    }

    if (!tzidSeen) {
        throw ParserException(generic.pos(), "The TZID property is required!");
    }

    for (auto &component : generic->getSubcomponents()) {
        auto &name = component->getName();
        if (*name == "STANDARD") {
            res.standardRules.emplace_back(
                        std::move(components::TimeZoneRules::parse(component)));
        } else if (*name == "DAYLIGHT") {
            res.dstRules.emplace_back(
                        std::move(components::TimeZoneRules::parse(component)));
        } else {
            throw ParserException(component.pos(), "Invalid component!");
        }
    }

    if (res.standardRules.size() == 0 && res.dstRules.size() == 0) {
        throw ParserException(generic.pos(),
                              "The " + NAME + " component must contain at least "
                              "one STANDARD or DAYLIGHT component!");
    }
    return res;
}

} // namespace components
} // namespace ical

