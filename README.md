# PA193 Project -- Team R

## Topic
Parser of the iCalendar format ([RFC 5545](https://tools.ietf.org/html/rfc5545)).

## Team members
 * Ondrej Mosnáček
 * Ľubomír Obrátil
 * Lenka Kuníková

## Language and dependencies
The parser is written in C++11 and has no additional dependencies (except the standard library).

## Parser Limitations
Due to limited time for the project and/or undue complexity of certain parts of the specification, the parser has the following known limitations:

 * The specification defines default encoding for iCalendar files to be UTF-8 ([section 3.1.4](https://tools.ietf.org/html/rfc5545#section-3.1.4)). Our parser validates UTF-8 encoding of the file, however all strings in the resulting in-memory structure are left UTF-8 encoded.
 * The parser does not validate URI references ([section 3.3.13](https://tools.ietf.org/html/rfc5545#section-3.3.13)) and calendar user addresses ([section 3.3.3](https://tools.ietf.org/html/rfc5545#section-3.3.3)).
 * The language tag ([section 3.2.10](https://tools.ietf.org/html/rfc5545#section-3.2.10)) is not validated.
 * The parser works in two stages, where in the first stage the file/stream is initially parsed into a generic tree structure, which is then further processed and validated into the final object representation. Therefore it may load the entire file/stream into memory before rejecting the invalid syntax.
