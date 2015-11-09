#ifndef VALUE_H
#define VALUE_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Value
{
private:
    std::string value;
public:
    static const std::string NAME;

    Value() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out) const;

    static Value parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical
#endif // VALUE_H
