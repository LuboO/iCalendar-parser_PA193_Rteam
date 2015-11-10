#include "core/valueparser.h"

#include "parserexception.h"

#include <regex>
#include <climits>

namespace ical {
namespace core {

/* NOTE: The standard defines the BOOLEAN value type, but defines no property
 * with this value type. We leave the method here for completeness. */
bool ValueParser::parseBoolean(const StreamPos &pos,
                               std::string::const_iterator begin,
                               std::string::const_iterator end)
{
    if (std::string(begin, end) == "TRUE") {
        return true;
    } else if (std::string(begin, end) == "FALSE") {
        return false;
    } else {
        throw ParserException(pos, "Invalid boolean value!");
    }
}

double ValueParser::parseFloat(const StreamPos &pos,
                               std::string::const_iterator begin,
                               std::string::const_iterator end)
{
    static const std::regex RE_FLOAT { "([-+]?)([0-9]+)(:?.([0-9]+))" };
    if (!std::regex_match(begin, end, RE_FLOAT)) {
        throw ParserException(pos, "Invalid float value!");
    }
    /* the regex already ensures correct format for std::stof: */
    try {
        return std::stod(std::string(begin, end));
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Float value out of range for double!");
    }
}

int ValueParser::parseInteger(const StreamPos &pos,
                              std::string::const_iterator begin,
                              std::string::const_iterator end)
{
    static const std::regex RE_INTEGER { "([-+]?)([0-9]+)" };
    if (!std::regex_match(begin, end, RE_INTEGER)) {
        throw ParserException(pos, "Invalid float value!");
    }
    /* the regex already ensures correct format for std::stoi: */
    try {
        return std::stoi(std::string(begin, end));
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Integer value out of range for int!");
    }
}

unsigned int ValueParser::parseUnsignedInteger(
        const StreamPos &pos,
        std::string::const_iterator begin,
        std::string::const_iterator end)
{
    static const std::regex RE_UINTEGER { "([0-9]+)" };
    if (!std::regex_match(begin, end, RE_UINTEGER)) {
        throw ParserException(pos, "Invalid float value!");
    }
    /* the regex already ensures correct format for std::stou: */
    try {
        auto ul = std::stoul(std::string(begin, end));
        if (ul > UINT_MAX) {
            throw std::out_of_range("");
        }
        return static_cast<unsigned int>(ul);
    } catch (std::out_of_range &) {
        throw ParserException(pos, "Unsigned integer value out of range for unsigned int!");
    }
}

void ValueParser::validateCalendarAddress(const StreamPos &pos,
                                          const std::string &value)
{
    return validateUri(pos, value);
}

void ValueParser::validateUri(const StreamPos &,
                              const std::string &)
{
    /* We decided not to validate this. */
}

std::string ValueParser::parseText(const StreamPos &pos,
                                   std::string::const_iterator begin,
                                   std::string::const_iterator end)
{
    std::string res;
    while (begin != end) {
        char c = *begin;
        if (c == ';' || c == ',') {
            throw ParserException(pos, "Invalid text character!");
        }
        if (c == '\\') {
            if (++begin == end) {
                throw ParserException(pos, "Incomplete escape sequence in text value!");
            }
            c = *begin;
            if (c == '\\' || c == ';' || c == ',') {
                res.push_back(c);
            } else if (c == 'n' || c == 'N') {
                res.push_back('\n');
            } else {
                throw ParserException(pos, "Invalid escape sequence in text value!");
            }
        } else {
            res.push_back(c);
        }
        ++begin;
    }
    return res;
}

static unsigned char base64value(const StreamPos &pos, char c)
{
    if (c >= 'A' && c <= 'Z') {
        return static_cast<unsigned char>(c - 'A');
    } else if (c >= 'a' && c <= 'z') {
        return static_cast<unsigned char>(c - 'a') + 26;
    } else if (c >= '0' && c <= '9') {
        return static_cast<unsigned char>(c - '0') + 2 * 26;
    } else if (c == '+') {
        return 2 * 26 + 10;
    } else if (c == '/') {
        return 2 * 26 + 10 + 1;
    } else {
        throw ParserException(pos, "Invalid base64 character!");
    }
}

static std::string base64decode(const StreamPos &pos,
                                std::string::const_iterator begin,
                                std::string::const_iterator end)
{
    auto inLength = static_cast<std::size_t>(end - begin);
    if (inLength % 4 != 0) {
        throw ParserException(pos, "Base64 sequence has invalid length!");
    }
    if (inLength == 0) {
        return {};
    }

    std::size_t outLength = (inLength / 4) * 3;
    std::size_t padding = 0;
    while (padding <= 2 && *(end - padding - 1) == '=') {
        ++padding;
    }
    outLength -= padding;

    std::string res;
    res.reserve(outLength);
    while (true) {
        unsigned long int val = 0;
        for (std::size_t i = 0; i < 4; i++) {
            val <<= 6;
            if (static_cast<std::size_t>(end - begin) > padding) {
                val |= base64value(pos, *begin);
            }
            ++begin;
        }
        res.push_back(static_cast<char>((val >> 16) & 0xFF)); --outLength;
        if (outLength == 0) {
            break;
        }
        res.push_back(static_cast<char>((val >>  8) & 0xFF)); --outLength;
        if (outLength == 0) {
            break;
        }
        res.push_back(static_cast<char>((val >>  0) & 0xFF)); --outLength;
        if (outLength == 0) {
            break;
        }
    }
    return res;
}

static std::string base64encode(const std::string &data)
{
    static const char *ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::size_t outLength = (data.size() * 4) / 3;

    std::string res;
    res.reserve(outLength);
    for (auto it = data.begin(); it != data.end(); ++it) {
        unsigned long int b = (*it & 0xFC) >> 2;
        res.push_back(ALPHABET[b]);

        b = (*it & 0x03) << 4;
        if (++it == data.end()) {
            res.push_back(ALPHABET[b]);
            res.push_back('=');
            res.push_back('=');
            break;
        }

        b |= (*it & 0xF0) >> 4;
        res.push_back(ALPHABET[b]);

        b = (*it & 0x0F) << 2;
        if (++it == data.end()) {
            res.push_back(ALPHABET[b]);
            res.push_back('=');
            break;
        }

        b |= (*it & 0xC0) >> 6;
        res.push_back(ALPHABET[b]);

        b = *it & 0x3F;
        res.push_back(ALPHABET[b]);
    }
    return res;
}

std::string ValueParser::parseBase64(const StreamPos &pos,
                                     std::string::const_iterator begin,
                                     std::string::const_iterator end)
{
    return base64decode(pos, begin, end);
}

std::string ValueParser::encodeText(const std::string &value)
{
    std::string res;
    for (char c : value) {
        switch (c) {
        case '\n':
            res.push_back('\\');
            res.push_back('n');
            break;
        case ';':
        case ',':
        case '\\':
            res.push_back('\\');
            res.push_back(c);
            break;
        default:
            res.push_back(c);
            break;
        }
    }
    return res;
}

std::string ValueParser::encodeBase64(const std::string &value)
{
    return base64encode(value);
}

std::string ValueParser::parseQuoted(const StreamPos &pos, const std::string &value)
{
    /* no need to check value.back() -- GenericParser would have caught it: */
    if (value.size() < 2 || value.front() != '"') {
        throw ParserException(pos, "Expected a quoted string!");
    }
    return value.substr(1, value.size() - 1);
}

std::string ValueParser::parsePossiblyQuoted(const StreamPos &, const std::string &value)
{
    if (value.size() == 0) {
        return value;
    } else if (value.front() == '"') {
        return value.substr(1, value.size() - 1);
    } else {
        return value;
    }
}

} // namespace core
} // namespace ical

