#ifndef ICAL_CORE_WITHPOS_H
#define ICAL_CORE_WITHPOS_H

#include "streampos.h"

namespace ical {
namespace core {

/**
 * A wrapper that stores the original position in the source stream
 * alongside a parsed value.
 *
 * This can be used when parsing the second level structure to report
 * more informative errors/exceptions.
 */
template<class T>
class WithPos
{
private:
    StreamPos position;
    T val;

public:
    const StreamPos &pos() const noexcept { return position; }

    T &value() noexcept { return val; }
    const T &value() const noexcept { return val; }

    WithPos(const StreamPos &pos, const T &value)
        : position(pos), val(value)
    {
    }
    WithPos(const StreamPos &pos, T &&value)
        : position(pos), val(value)
    {
    }

    /*
     * Pointer semantics to get the value (for convenience).
     *
     * This means for a variable `x` of type `WithPos<...>`
     * `x -> <method>(...)` is the same as `x.val().<method>(...)`
     * and `*x` is the same as `x.val()`.
     */
    T &operator*() noexcept
    {
        return val;
    }

    const T &operator*() const noexcept
    {
        return val;
    }

    T *operator->() noexcept
    {
        return &val;
    }

    const T *operator->() const noexcept
    {
        return &val;
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_WITHPOS_H
