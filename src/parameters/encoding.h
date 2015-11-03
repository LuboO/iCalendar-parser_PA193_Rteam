#ifndef ICAL_PARAMETERS_ENCODING_H
#define ICAL_PARAMETERS_ENCODING_H

#include <ostream>
#include <vector>
#include <string>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Encoding
{
private:
    std::string value;
public:
    Encoding() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out);

    static Encoding parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // ICAL_PARAMETERS_ENCODING_H

