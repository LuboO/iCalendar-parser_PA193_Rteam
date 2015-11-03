#ifndef ICAL_CORE_STREAM_H
#define ICAL_CORE_STREAM_H

#include "streampos.h"
#include "parserexception.h"
#include "core/utf8validator.h"

#include <cstddef>

#ifdef DEBUG
#include <stdexcept>
#endif

namespace ical {
namespace core {

/** A helper to read an iCalendar stream from char iterators. */
template<class InputIterator>
class Stream
{
private:
    InputIterator it;
    InputIterator end;

    StreamPos pos;
    UTF8Validator validator;

    /*
     * If '\r' is encountered, we need to look ahead up to 3 characters
     * (because "\r\n( |\t)" is to be ignored), therefore we keep track
     * of which characters we have read from the iterator that haven't
     * been read from us yet:
     */
    enum {
        NORMAL,
        CRLF,
        CR,
        LF
    } state = NORMAL;

    void checkLineFold()
    {
        state = NORMAL;
        while (!isEnd() && *it == '\r') {
            ++it;
            if (isEnd() || *it != '\n') {
                /* CR not followed by LF */
                state = CR;
                break;
            }
            ++it;
            if (isEnd() || (*it != ' ' && *it != '\t')) {
                /* just CRLF */
                state = CRLF;
                break;
            }
            /* CRLF followed by a space/tab */
            /* ignored as per RFC5545, section 3.1 */
            ++it;
            pos.advanceLine();
            pos.advanceColumn();
        }
    }

    void checkUtf8()
    {
        bool utf8check = isEnd() ? validator.checkEnd() :
                                   validator.checkNext(peek());
        if (!utf8check) {
            throw ParserException(pos, "Invalid UTF-8 sequence!");
        }
    }

public:
    const StreamPos &getPosition() const { return pos; }

    Stream(InputIterator begin, InputIterator end)
        : it(begin), end(end), pos(), validator()
    {
        checkLineFold();
        checkUtf8();
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
            checkUtf8();
            return '\r';
        }
        if (state == CR) {
            pos.advanceColumn();
            checkLineFold();
            checkUtf8();
            return '\r';
        }
        if (state == LF) {
            pos.advanceLine();
            checkLineFold();
            checkUtf8();
            return '\n';
        }
        char ret = *(it++);
        pos.advanceColumn();
        checkLineFold();
        checkUtf8();
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
            checkUtf8();
        } else if (state == CR) {
            pos.advanceColumn();
            checkLineFold();
            checkUtf8();
        } else if (state == LF) {
            pos.advanceLine();
            checkLineFold();
            checkUtf8();
        } else {
            ++it;
            pos.advanceColumn();
            checkLineFold();
            checkUtf8();
        }
    }
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_STREAM_H
