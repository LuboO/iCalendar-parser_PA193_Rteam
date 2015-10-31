#ifndef ICAL_STREAMPOS_H
#define ICAL_STREAMPOS_H


namespace ical {

/**
 * Represents a postion in the (source) stream. It is used for constructing
 * nice error messages.
 *
 * Note: only CRLF ("\r\n") is considered as a line ending in order to match
 * the definition of 'content line' from RFC 5545.
 */
class StreamPos
{
private:
    unsigned long column = 0;
    unsigned long line = 0;

public:
    unsigned long getLine() const { return line; }
    unsigned long getColumn() const { return column; }

    StreamPos() { }

    void advanceColumn()
    {
        ++column;
    }

    void advanceLine()
    {
        column = 0;
        ++line;
    }
};

} // namespace ical

#endif // ICAL_STREAMPOS_H
