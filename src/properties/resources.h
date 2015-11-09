#ifndef ICAL_PROPERTIES_RESOURCES_H
#define ICAL_PROPERTIES_RESOURCES_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"
#include "parameters/altrep.h"

namespace ical {
namespace properties {

class Resources
{
private:
    std::vector<std::string> values;
    std::vector<parameters::AltRep> altRepParam;
    std::vector<parameters::Language> languageParam;
public:
    static const std::string NAME;

    Resources() {}

    void print(std::ostream & out) const;

    static Resources parse(const core::WithPos<core::GenericProperty> &generic);

    const std::vector<std::string> &getValues() const noexcept  {  return values;  }
    const std::vector<parameters::AltRep> &getAltRepParam() const noexcept { return altRepParam; }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_RESOURCES_H

