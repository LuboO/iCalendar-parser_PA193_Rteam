#ifndef ICAL_PROPERTIES_CATEGORIES_H
#define ICAL_PROPERTIES_CATEGORIES_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"

namespace ical {
namespace properties {

class Categories
{
private:
    std::vector<std::string> values;
    std::vector<parameters::Language> languageParam;
public:
    Categories() {}

    void print(std::ostream & out) const;

    static Categories parse(const core::WithPos<core::GenericProperty> &generic);

    const std::vector<std::string> &getValues() const noexcept  {  return values;  }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_CATEGORIES_H

