#ifndef ICAL_COMPONENTS_VTIMEZONE_H
#define ICAL_COMPONENTS_VTIMEZONE_H

#include "core/genericcomponent.h"
#include "core/uniqueidregistry.h"

#include "properties/tzid.h"
#include "properties/lastmodified.h"
#include "properties/tzurl.h"

#include "components/timezonerules.h"

#include <ostream>
#include <vector>

namespace ical {
namespace components {

class VTimeZone
{
private:
    properties::TZId tzid;
    std::vector<properties::LastModified> lastModified;
    std::vector<properties::TZUrl> tzUrl;
    std::vector<components::TimeZoneRules> standardRules;
    std::vector<components::TimeZoneRules> dstRules;

public:
    static const std::string NAME;

    const properties::TZId &getTZID() const noexcept { return tzid; }
    const std::vector<properties::LastModified> &getLastModified() const noexcept
    {
        return lastModified;
    }
    const std::vector<properties::TZUrl> &getTZUrl() const noexcept
    {
        return tzUrl;
    }
    const std::vector<components::TimeZoneRules> &getStandardTimeRules() const noexcept
    {
        return standardRules;
    }
    const std::vector<components::TimeZoneRules> &getDSTRules() const noexcept
    {
        return dstRules;
    }

    VTimeZone() : lastModified(), tzUrl(), standardRules(), dstRules() { }

    void print(std::ostream &out) const;

    static VTimeZone parse(const core::WithPos<core::GenericComponent> &generic,
                           core::UniqueIdRegistry &tzidRegistry);
};

} // namespace components
} // namespace ical

#endif // ICAL_COMPONENTS_VTIMEZONE_H
