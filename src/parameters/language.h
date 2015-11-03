#ifndef ICAL_PARAMETERS_LANGUAGE_H
#define ICAL_PARAMETERS_LANGUAGE_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Language
{
private:
    std::string value;
public:
    Language() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream &out) const;

    static Language parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_LANGUAGE_H

