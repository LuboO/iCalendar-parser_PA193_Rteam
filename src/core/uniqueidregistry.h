#ifndef ICAL_CORE_UNIQUEIDREGISTRY_H
#define ICAL_CORE_UNIQUEIDREGISTRY_H

#include <unordered_set>
#include <string>

namespace ical {
namespace core {

class UniqueIdRegistry
{
private:
    std::unordered_set<std::string> ids;

public:
    UniqueIdRegistry() : ids() { }

    /**
     * Adds a new ID into the registry.
     *
     * @param id the ID to add
     *
     * @return `true`, if the ID was NOT already in the registry;
     *         `false` otherwise.
     */
    bool registerId(const std::string &id)
    {
        return ids.insert(id).second;
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_UNIQUEIDREGISTRY_H
