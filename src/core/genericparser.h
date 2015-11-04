#ifndef ICAL_CORE_GENERICPARSER_H
#define ICAL_CORE_GENERICPARSER_H

#include "parserexception.h"

#include "core/charset.h"
#include "core/stream.h"
#include "core/genericcomponent.h"

#include <algorithm>

namespace ical {
namespace core {

/** A parser that parses the generic structure of an iCalendar file */
class GenericParser
{
private:
    /* Character matching bitmaps for different tokens: */
    static const CharSet CONTROL;
    static const CharSet WSP;
    static const CharSet ALPHANUMERIC;

    static const CharSet IANA_TOKEN;
    static const CharSet QSAFE_CHAR;
    static const CharSet SAFE_CHAR;
    static const CharSet VALUE_CHAR;

    /** A helper template (so the functions can share the 'stream' field). */
    template<class InputCharIterator>
    class Parser
    {
    private:
        Stream<InputCharIterator> stream;

        /** Asserts this is not the end of stream. */
        void checkEndOfStream()
        {
            if (stream.isEnd()) {
                throw ParserException(
                            stream.getPosition(),
                            "Unexpected end of stream!");
            }
        }

        /** 'Normalizes' a string (converts it to uppercase). */
        static void normalize(std::string &str)
        {
            std::transform(str.begin(), str.end(), str.begin(),
                           [](char x) { return std::toupper(x); });
        }

        /** Checks if the content line is a valid BEGIN c. l. */
        static void checkBeginContentLine(const WithPos<GenericProperty> &line)
        {
            if (!line->getParameters().empty()) {
                throw ParserException(
                            line.pos(),
                            "BEGIN content line must not have parameters!");
            }
        }

        /**
         * Parses a token (longest possible string with chars from
         * `allowedChars`).
         *
         * When the function returns. the stream is positioned
         * just after the parsed token.
         *
         * @param allowedChars  the set of allowed characters
         *
         * @tparam Normalize    if true, then the token is normalized
         */
        template<bool Normalize = false>
        WithPos<std::string> parseToken(CharSet allowedChars)
        {
            /* snapshot starting position: */
            StreamPos startPos = stream.getPosition();

            std::string token;
            while (true) {
                if (stream.isEnd()) {
                    break;
                }
                char c = stream.peek();
                if (Normalize) {
                    c = std::toupper(c);
                }
                if (!allowedChars.match(c)) {
                    break;
                }
                token.push_back(c);
                stream.advance();
            }
            return { std::move(startPos), std::move(token) };
        }

        /**
         * Asserts that the given string follows in the stream.
         *
         * When the function returns. the stream is positioned
         * just after the matched string.
         */
        void expectString(const std::string &str)
        {
            /* snapshot starting position: */
            StreamPos startPos = stream.getPosition();

            for (auto c : str) {
                checkEndOfStream();

                if (stream.next() != c) {
                    throw ParserException(
                                startPos,
                                "Expected '" + str + "'!");
                }
            }
        }

        /** Parses a parameter value. */
        WithPos<std::string> parseParamValue()
        {
            StreamPos pos = stream.getPosition();

            checkEndOfStream();

            std::string value;

            char c = stream.peek();
            if (c == '"') {
                stream.advance();
                value = "\"" + *parseToken<true>(QSAFE_CHAR) + "\"";
                expectString("\"");
            } else {
                value = *parseToken<true>(SAFE_CHAR);
            }
            return { std::move(pos), std::move(value) };
        }

        /** Parses a property parameter and puts into the given vector. */
        void parseParam(std::vector<WithPos<GenericPropertyParameter>> &out)
        {
            StreamPos pos = stream.getPosition();
            auto name = parseToken<true>(IANA_TOKEN);
            expectString("=");

            std::vector<WithPos<std::string>> values;
            do {
                values.emplace_back(std::move(parseParamValue()));
            } while (stream.peek() == ',');

            out.emplace_back(std::move(pos), GenericPropertyParameter(
                                 std::move(name), std::move(values)));
        }

        /** Parses a content line and returns it as a `GenericProperty`. */
        WithPos<GenericProperty> parseContentLine()
        {
            StreamPos pos = stream.getPosition();

            auto name = parseToken<true>(IANA_TOKEN);

            std::vector<WithPos<GenericPropertyParameter>> params;
            checkEndOfStream();
            while (stream.peek() == ';') {
                stream.advance();
                parseParam(params);
            }

            expectString(":");

            auto value = parseToken(VALUE_CHAR);

            expectString("\r\n");

            return { pos, GenericProperty(name, value, params) };
        }

        /** Parses the content of a component. */
        void parseComponentContent(const StreamPos &startPos,
                                   const WithPos<std::string> &componentName,
                                   std::vector<WithPos<GenericComponent>> &out)
        {
            std::vector<WithPos<GenericProperty>> properties;
            std::vector<WithPos<GenericComponent>> subcomponents;

            WithPos<GenericProperty> line = parseContentLine();
            /* parse properties: */
            while (*line->getName() != "BEGIN" && *line->getName() != "END") {
                properties.push_back(std::move(line));

                line = parseContentLine();
            }
            /* parse subcomponents: */
            while (*line->getName() == "BEGIN") {
                checkBeginContentLine(line);

                WithPos<std::string> componentName = line->getValue();
                normalize(componentName.value());
                parseComponentContent(line.pos(), componentName, subcomponents);

                line = parseContentLine();
            }
            if (*line->getName() != "END") {
                throw ParserException(
                            line.pos(),
                            "Expected a BEGIN or END content line!");
            }
            if (*line->getValue() != *componentName) {
                throw ParserException(
                            line->getValue().pos(),
                            "END content line value must match the component's name!");
            }
            if (!line->getParameters().empty()) {
                throw ParserException(
                            line.pos(),
                            "END content line must not have parameters!");
            }

            out.emplace_back(startPos, GenericComponent { componentName,
                std::move(properties), std::move(subcomponents) });
        }

    public:
        Parser(InputCharIterator begin, InputCharIterator end)
            : stream(begin, end)
        {
        }

        std::vector<WithPos<GenericComponent>> parse()
        {
            std::vector<WithPos<GenericComponent>> res;
            /* the components must be strictly consecutive, */
            /* nothing must follow after them: */
            while (!stream.isEnd()) {
                auto line = parseContentLine();
                if (*line->getName() != "BEGIN") {
                    throw ParserException(
                                line.pos(),
                                "Expected a BEGIN content line!");
                }
                checkBeginContentLine(line);

                WithPos<std::string> componentName = line->getValue();
                normalize(componentName.value());

                parseComponentContent(line.pos(), componentName, res);
            }
            return res;
        }
    };

public:
    /**
     * Parses the generic structure of an iCalendar stream
     * from a pair of input forward iterators.
     *
     * @throws `ical::ParserException` syntax error
     */
    template<class InputCharIterator>
    static std::vector<WithPos<GenericComponent>> parseStream(
            InputCharIterator begin, InputCharIterator end)
    {
        Parser<InputCharIterator> parser { begin, end };
        return std::move(parser.parse());
    }

    static std::vector<WithPos<GenericComponent>> parseStream(std::istream &stream);
};

} // namespace core
} // namespace ical

#endif // ICAL_CORE_GENERICPARSER_H
