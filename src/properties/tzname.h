#ifndef ICAL_PROPERTIES_TZNAME_H
#define ICAL_PROPERTIES_TZNAME_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"

namespace ical {
namespace properties {

class TZName
{
private:
    std::string value;
    std::vector<parameters::Language> langParam;
public:
    TZName() {}

    const std::string &getValue() const noexcept { return value; }

    const std::vector<parameters::Language> &getLangParameter() const noexcept {
        return langParam;
    }

    void print(std::ostream & out);

    static TZName parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_TZNAME_H

