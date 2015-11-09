#ifndef ICAL_CORE_UTF8VALIDATOR_H
#define ICAL_CORE_UTF8VALIDATOR_H

namespace ical {
namespace core {

/** A simple UTF-8 validator. */
class UTF8Validator
{
private:
    enum {
        /* the order of the following 4 values MUST be preserved! */
        STATE_INITIAL,
        STATE_TAIL1,
        STATE_TAIL2,
        STATE_TAIL3,

        STATE_MB3_1,
        STATE_MB3_2,
        STATE_MB4_1,
        STATE_MB4_2,
    };

    int state;

public:
    UTF8Validator()
        : state(STATE_INITIAL)
    {
    }

    /**
     * Checks the next octet of the UTF-8 stream and updates the validator
     * state. Returns true if the octet is valid for current state, false
     * otherwise.
     */
    bool checkNext(unsigned char c);

    /**
     * Checks whether the end of stream is valid for this state.
     */
    bool checkEnd() const noexcept { return state == STATE_INITIAL; }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_UTF8VALIDATOR_H
