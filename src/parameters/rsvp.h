#ifndef RSVP_H
#define RSVP_H

#include <ostream>
#include <vector>

#include "core/genericpropertyparameter.h"
#include "parserexception.h"

namespace ical {
namespace parameters {

class Rsvp
{
    std::string value;
public:
    static const std::string NAME;

    Rsvp() {}

    const std::string &getValue() const noexcept { return value; }

    void print(std::ostream & out) const;

    static Rsvp parse(const core::WithPos<core::GenericPropertyParameter> &generic);
};

} // namespace parameters
} // namespace ical


#endif // RSVP_H
