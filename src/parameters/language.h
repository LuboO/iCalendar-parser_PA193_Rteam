#ifndef ICAL_PARAMETERS_LANGUAGE_H
#define ICAL_PARAMETERS_LANGUAGE_H

#include <ostream>
#include <vector>

#include "core/genericcomponent.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Language
{
public:
    Language() {}

    void print(std::ostream & out);

    static Language parse(const core::WithPos<core::GenericComponent> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_LANGUAGE_H

