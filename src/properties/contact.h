#ifndef ICAL_PROPERTIES_CONTACT_H
#define ICAL_PROPERTIES_CONTACT_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"

namespace ical {
namespace properties {

class Contact
{
private:
    std::string value;
    //std::vector<parameters::Altrep> altrepParam;
    std::vector<parameters::Language> languageParam;

public:
    Contact() {}

    void print(std::ostream &out) const;

    static Contact parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    //const std::vector<parameters::Altrep> getAltrepParam() const noexcept { return altrepParam; }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PROPERTIES_CONTACT_H

