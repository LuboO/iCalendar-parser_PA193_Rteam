#ifndef RELTYPE_H
#define RELTYPE_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Reltype
{
private:
    std::string value;
public:
    static const std::string NAME;

    Reltype() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out) const;

    static Reltype parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // RELTYPE_H
