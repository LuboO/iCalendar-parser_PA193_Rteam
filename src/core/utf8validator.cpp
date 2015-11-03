#include "utf8validator.h"

#include <stdexcept>

namespace ical {
namespace core {

bool UTF8Validator::checkNext(unsigned char c) noexcept
{
    /* See https://tools.ietf.org/html/rfc3629#section-4
     * for the rationale of this algorithm: */
    switch (state) {
    case STATE_INITIAL:
        if ((c & 0x80) == 0) {
            /* single-byte character, stay in INITIAL */
            return true;
        } else if ((c & 0x40) == 0) {
            /* MB tail, invalid in this state */
            return false;
        } else if ((c & 0x20) == 0) {
            /* two-byte character */
            if ((c & 0x1F) < 0x02) {
                /* invalid codepoint for this category */
                return false;
            }
            state = STATE_TAIL1;
        } else if ((c & 0x10) == 0) {
            /* three-byte character */
            unsigned char lo_bits = c & 0x0F;
            if (lo_bits == 0x00) {
                state = STATE_MB3_1;
            } else if (lo_bits == 0x0D) {
                state = STATE_MB3_2;
            } else {
                state = STATE_TAIL2;
            }
        } else if ((c & 0x08) == 0) {
            /* four-byte character */
            unsigned char lo_bits = c & 0x07;
            if (lo_bits > 0x04) {
                /* invalid codepoint for this category */
                return false;
            } else if (lo_bits == 0x00) {
                state = STATE_MB4_1;
            } else if (lo_bits == 0x04) {
                state = STATE_MB4_2;
            } else {
                state = STATE_TAIL3;
            }
        } else {
            return false;
        }
        return true;
    case STATE_TAIL1:
    case STATE_TAIL2:
    case STATE_TAIL3:
        if ((c & 0xC0) != 0x80) {
            /* invalid tail octet */
            return false;
        }
        --state; /* go to the preceding state */
        return true;
    case STATE_MB3_1:
        if (c < 0xA0 || c > 0xBF) {
            /* invalid codepoint for this category */
            return false;
        }
        state = STATE_TAIL1;
        return true;
    case STATE_MB3_2:
        if (c < 0x80 || c > 0x9F) {
            /* invalid codepoint for this category */
            return false;
        }
        state = STATE_TAIL1;
        return true;
    case STATE_MB4_1:
        if (c < 0x90 || c > 0xBF) {
            /* invalid codepoint for this category */
            return false;
        }
        state = STATE_TAIL2;
        return true;
    case STATE_MB4_2:
        if (c < 0x80 || c > 0x8F) {
            /* invalid codepoint for this category */
            return false;
        }
        state = STATE_TAIL2;
        return true;
    default:
        throw std::logic_error("Invalid validator state!");
    }
}

} // namespace core
} // namespace ical

