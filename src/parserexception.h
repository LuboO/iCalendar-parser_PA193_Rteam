#ifndef ICAL_PARSEREXCEPTION_H
#define ICAL_PARSEREXCEPTION_H

#include "streampos.h"

#include <stdexcept>
#include <sstream>

namespace ical {

class ParserException : public std::runtime_error
{
private:
    StreamPos pos;
    std::string message;

    static std::string buildWhat(const StreamPos &pos,
                                 const std::string &message)
    {
        std::ostringstream oss;
        oss << "Line " << pos.getLine() << ", column " << pos.getColumn()
            << ": " << message;
        return oss.str();
    }

public:
    const StreamPos &getPosition() const noexcept { return pos; }
    const std::string &getMessage() const noexcept { return message; }

    ParserException(const StreamPos &pos, const std::string &message)
        : std::runtime_error(buildWhat(pos, message)),
          pos(pos), message(message)
    {
    }
};

} // namespace ical

#endif // ICAL_PARSEREXCEPTION_H
