#ifndef ICAL_CORE_WITHPOS_H
#define ICAL_CORE_WITHPOS_H

#include "streampos.h"

namespace ical {
namespace core {

template<class T>
class WithPos
{
private:
    StreamPos position;
    T val;

public:
    const StreamPos &pos() const noexcept { return position; }
    T &value() { return val; }
    const T &value() const { return val; }

    WithPos(const StreamPos &pos, const T &value)
        : position(pos), val(value)
    {
    }
    WithPos(const StreamPos &pos, T &&value)
        : position(pos), val(value)
    {
    }

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
