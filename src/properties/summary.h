#ifndef ICAL_PROPERTIES_SUMMARY_H
#define ICAL_PROPERTIES_SUMMARY_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Summary
{
public:
    Summary() {}

    void print(std::ostream & out) const;

    static Summary parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_SUMMARY_H

