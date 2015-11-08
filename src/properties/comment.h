#ifndef ICAL_PROPERTIES_COMMENT_H
#define ICAL_PROPERTIES_COMMENT_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

#include "parameters/language.h"
#include "parameters/altrep.h"

namespace ical {
namespace properties {

class Comment
{
private:
    std::string value;
    std::vector<parameters::AltRep> altRepParam;
    std::vector<parameters::Language> languageParam;
public:
    Comment() {}

    void print(std::ostream & out) const;

    static Comment parse(const core::WithPos<core::GenericProperty> &generic);

    const std::string &getValue() const noexcept { return value; }
    const std::vector<parameters::AltRep> &getAltRepParam() const noexcept { return altRepParam; }
    const std::vector<parameters::Language> &getLanguageParam() const noexcept { return languageParam; }
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_COMMENT_H

