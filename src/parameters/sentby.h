#ifndef SENTBY_H
#define SENTBY_H

#include <ostream>
#include <vector>
#include <regex>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class SentBy
{
    std::string value;
public:
    SentBy() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out) const;

    static SentBy parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical

#endif // SENTBY_H
