#include "comment.h"

namespace ical {
namespace properties {

void Comment::print(std::ostream &out) const {

}

Comment Comment::parse(const core::WithPos<core::GenericProperty> &generic) {
    return {};
}

} // namespace properties
} // namespace ical

