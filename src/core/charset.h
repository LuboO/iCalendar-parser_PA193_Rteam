#ifndef ICAL_CORE_CHARSET_H
#define ICAL_CORE_CHARSET_H

#include <bitset>
#include <limits>

#ifdef DEBUG
#include <stdexcept>
#endif

namespace ical {
namespace core {

/**
 * A helper class for testing whether a character belongs to a set
 * in an efficient manner (using std::bitset).
 */
class CharSet
{
private:
    typedef std::bitset<std::numeric_limits<char>::max()> bitset;

    static bitset bs_range(unsigned char s, unsigned char e)
    {
#ifdef DEBUG
        if (s > e) {
            throw std::logic_error("Starting character must be <= the ending character!");
        }
#endif

        bitset res;
        for (auto c = s; c <= e; c++) {
            res.set(c);
        }
        return std::move(res);
    }

    bitset bs;

    CharSet(bitset bs) noexcept
        : bs(bs)
    {
    }

public:
    CharSet() noexcept
        : bs()
    {
    }

    CharSet(char c) noexcept
        : bs(bitset(1) << static_cast<unsigned char>(c))
    {
    }

    CharSet(char s, char e)
        : bs(bs_range(s, e))
    {
    }

    bool match(char c) const noexcept
    {
        return bs.test(static_cast<unsigned char>(c));
    }

    CharSet operator~() const noexcept
    {
        return ~bs;
    }

    CharSet operator|(const CharSet &other) const noexcept
    {
        return bs | other.bs;
    }

    CharSet operator&(const CharSet &other) const noexcept
    {
        return bs & other.bs;
    }

    CharSet operator^(const CharSet &other) const noexcept
    {
        return bs ^ other.bs;
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_CHARSET_H
