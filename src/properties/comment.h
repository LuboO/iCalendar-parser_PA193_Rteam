#ifndef ICAL_PROPERTIES_COMMENT_H
#define ICAL_PROPERTIES_COMMENT_H

#include <ostream>
#include <vector>

#include "core/genericproperty.h"
#include "parserexception.h"

namespace ical {
namespace properties {

class Comment
{
public:
    Comment() {}

    void print(std::ostream & out) const;

    static Comment parse(const core::WithPos<core::GenericProperty> &generic);
};

} // namespace properties
} // namespace ical

#endif // ICAL_PARAMETERS_COMMENT_H

