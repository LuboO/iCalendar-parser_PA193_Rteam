#ifndef ICAL_PROPERTIES_DESCRIPTION_H
#define ICAL_PROPERTIES_DESCRIPTION_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"
#include "parameters/altrep.h"

namespace ical {
namespace properties {

class Description
{
private:
    std::string value;
    std::vector<parameters::AltRep> altRepParam;
    std::vector<parameters::Language> languageParam;
public:
    static const std::string NAME;

    Description() {}

    void print(std::ostream & out) const;

    static Description parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    const std::vector<parameters::AltRep> &getAltRepParam() const noexcept { return altRepParam; }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_DESCRIPTION_H

