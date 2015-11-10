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
 *
 * This class uses a CHAR_MAX-bit bitset to track which character belongs
 * to the set and which doesn't. A character with value `x` belongs to
 * the set if and only if the `x`-th bit is set in the underlying bitset.
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
        return res;
    }

    bitset bs;

    /* NOTE: The following constructor is implicit for convenience: */
    CharSet(bitset bs) noexcept
        : bs(bs)
    {
    }

public:
    /** Constructs an empty set. */
    CharSet() noexcept
        : bs()
    {
    }

    /* NOTE: The following constructor is implicit for convenience: */
    /** Constructs a set containing a single character. */
    CharSet(char c) noexcept
        : bs(bitset(1) << static_cast<unsigned char>(c))
    {
    }

    /**
     * Constructs a set containing a range of characters.
     *
     * @param s lower bound of the range (inclusive)
     * @param e upper bound of the range (inclusive)
     */
    CharSet(char s, char e)
        : bs(bs_range(s, e))
    {
    }

    /** Returns true if the character belongs to the set, otherwise false. */
    bool match(char c) const noexcept
    {
        return bs.test(static_cast<unsigned char>(c));
    }

    /** Returns the complement of the set. */
    CharSet operator~() const noexcept
    {
        return ~bs;
    }

    /** Returns the union with another set. */
    CharSet operator|(const CharSet &other) const noexcept
    {
        return bs | other.bs;
    }

    /** Returns the intersection with another set. */
    CharSet operator&(const CharSet &other) const noexcept
    {
        return bs & other.bs;
    }

    /** Returns the symmetric difference with another set. */
    CharSet operator^(const CharSet &other) const noexcept
    {
        return bs ^ other.bs;
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_CHARSET_H
