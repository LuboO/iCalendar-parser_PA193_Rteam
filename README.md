# PA193 Project &ndash; Team R

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
 * In many places, the specification allows the occurence of extension components/properties/property parameters. Our parser rejects these entities (otherwise there wouldn't be much to validate about the format).
 * The format type tag ([section 3.2.8](https://tools.ietf.org/html/rfc5545#section-3.2.8)) is validated only for correct format (type-name/subtype-name) but not for valid names.
 * The language tag ([section 3.2.10](https://tools.ietf.org/html/rfc5545#section-3.2.10)) is not validated.
 * The value of Method property ([3.7.2](https://tools.ietf.org/html/rfc5545#section-3.7.2)) is not checked, only the general IANA token syntax is validated.
 * When parsing an explicit period of time ([section 3.3.9](https://tools.ietf.org/html/rfc5545#section-3.3.9)), it is not checked whether the end date is after the start date.
 * When parsing a recurrence rule ([section 3.3.10](https://tools.ietf.org/html/rfc5545#section-3.3.10)), the type of the UNTIL part is not checked against the type of the DTSTART property. Next, the consistency of the UTC flag is not checked.
 * It is not verified that a VTIMEZONE ([section 3.6.5](https://tools.ietf.org/html/rfc5545#section-3.6.5)) component exists for each timezone identifier reffered to in the document.
 * The ^-escaping mechanism specified in [RFC 6868](https://tools.ietf.org/html/rfc6868) is not implemented.
 * The parser works in two stages, where in the first stage the file/stream is initially parsed into a generic tree structure, which is then further processed and validated into the final object representation. Therefore it may load the entire file/stream into memory before rejecting the invalid syntax.
