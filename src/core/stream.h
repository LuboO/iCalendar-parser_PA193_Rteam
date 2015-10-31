#ifndef ICAL_CORE_STREAM_H
#define ICAL_CORE_STREAM_H

#include "streampos.h"

#include <cstddef>

#ifdef DEBUG
#include <stdexcept>
#endif

namespace ical {
namespace core {

// TODO: validate UTF-8
/** A helper to read an iCalendar stream from char iterators. */
template<class InputIterator>
class Stream
{
private:
    InputIterator it;
    InputIterator end;

    StreamPos pos;

    enum {
        NORMAL,
        CRLF,
        CR,
        LF
    } state = NORMAL;

    void checkLineFold()
    {
        state = NORMAL;
        while (*it == '\r') {
            ++it;
            if (*it != '\n') {
                /* CR not followed by LF */
                state = CR;
                break;
            }
            ++it;
            if (*it == ' ' || *it == '\t') {
                /* CRLF followed by a space/tab */
                /* ignored as per RFC5545, section 3.1 */
                ++it;
                pos.advanceLine();
                pos.advanceColumn();
            } else {
                /* just CRLF */
                state = CRLF;
                break;
            }
        }
    }

public:
    const StreamPos &getPosition() const { return pos; }

    Stream(InputIterator begin, InputIterator end)
        : it(begin), end(end), pos()
    {
        checkLineFold();
    }

    bool isEnd() const
    {
        return state == NORMAL && it == end;
    }

    char peek() const
    {
#ifdef DEBUG
        if (isEnd()) {
            throw std::logic_error("Reading past the end of stream!");
        }
#endif
        if (state == CRLF || state == CR) {
            return '\r';
        }
        if (state == LF) {
            return '\n';
        }
        return *it;
    }

    char next()
    {
#ifdef DEBUG
        if (isEnd()) {
            throw std::logic_error("Reading past the end of stream!");
        }
#endif
        if (state == CRLF) {
            state = LF;
            pos.advanceColumn();
            return '\r';
        }
        if (state == CR) {
            pos.advanceColumn();
            checkLineFold();
            return '\r';
        }
        if (state == LF) {
            pos.advanceLine();
            checkLineFold();
            return '\n';
        }
        char ret = *(it++);
        pos.advanceColumn();
        checkLineFold();
        return ret;
    }

    void advance()
    {
#ifdef DEBUG
        if (isEnd()) {
            throw std::logic_error("Reading past the end of stream!");
        }
#endif
        if (state == CRLF) {
            state = LF;
            pos.advanceColumn();
        } else if (state == CR) {
            pos.advanceColumn();
            checkLineFold();
        } else if (state == LF) {
            pos.advanceLine();
            checkLineFold();
        } else {
            ++it;
            pos.advanceColumn();
            checkLineFold();
        }
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_STREAM_H
