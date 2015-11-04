#ifndef ICAL_PROPERTIES_ORGANIZER_H
#define ICAL_PROPERTIES_ORGANIZER_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/sentby.h"
#include "parameters/language.h"

namespace ical {
namespace properties {

class Organizer
{
private:
    std::string value;
    //std::vector<parameters::CN> cnParam;
    //std::vector<parameters::Dir> dirParam;
    std::vector<parameters::SentBy> sentByParam;
    std::vector<parameters::Language> languageParam;
public:
    Organizer() {}

    void print(std::ostream &out) const;

    static Organizer parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    //const std::vector<parameters::CN> &getCnParam() const noexcept { return cnParam; }
    //const std::vector<parameters::Dir> &getDirParam() const noexcept { return dirParam; }
    const std::vector<parameters::SentBy> &getSentByParam() const noexcept { return sentByParam; }
    const std::vector<parameters::Language> getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_ORGANIZER_H

