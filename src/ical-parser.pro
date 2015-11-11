TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
QMAKE_CXXFLAGS_DEBUG += -DDEBUG

SOURCES += main.cpp \
    core/genericparser.cpp \
    components/vcalendar.cpp \
    core/valueparser.cpp \
    data/recurrencerule.cpp \
    data/utcoffset.cpp \
    data/date.cpp \
    data/datetime.cpp \
    data/duration.cpp \
    data/period.cpp \
    data/time.cpp \
    components/vevent.cpp \
    components/vjournal.cpp \
    components/vtodo.cpp \
    components/vfreebusy.cpp \
    components/vtimezone.cpp \
    components/valarm.cpp \
    parameters/encoding.cpp \
    parameters/fmttype.cpp \
    properties/tzid.cpp \
    parameters/fbtype.cpp \
    parameters/language.cpp \
    parameters/member.cpp \
    parameters/partstat.cpp \
    parameters/range.cpp \
    parameters/related.cpp \
    properties/tzname.cpp \
    properties/tzoffsetfrom.cpp \
    properties/tzoffsetto.cpp \
    properties/tzurl.cpp \
    properties/attendee.cpp \
    properties/contact.cpp \
    properties/organizer.cpp \
    properties/recurrenceid.cpp \
    properties/relatedto.cpp \
    properties/url.cpp \
    properties/uid.cpp \
    properties/requeststatus.cpp \
    core/utf8validator.cpp \
    parameters/reltype.cpp \
    parameters/role.cpp \
    parameters/rsvp.cpp \
    parameters/sentby.cpp \
    parameters/tzid_param.cpp \
    parameters/value.cpp \
    properties/action.cpp \
    properties/created.cpp \
    properties/dtstamp.cpp \
    properties/exdate.cpp \
    properties/lastmodified.cpp \
    properties/rdate.cpp \
    properties/repeat.cpp \
    properties/rrule.cpp \
    properties/sequence.cpp \
    properties/trigger.cpp \
    parameters/altrep.cpp \
    parameters/calusertype.cpp \
    parameters/commonname.cpp \
    parameters/delegatedfrom.cpp \
    parameters/delegatedto.cpp \
    parameters/direntryref.cpp \
    properties/attach.cpp \
    properties/categories.cpp \
    properties/class.cpp \
    properties/comment.cpp \
    properties/description.cpp \
    properties/geo.cpp \
    properties/location.cpp \
    properties/percentcomplete.cpp \
    properties/priority.cpp \
    properties/resources.cpp \
    properties/status.cpp \
    properties/summary.cpp \
    properties/completed.cpp \
    properties/dtend.cpp \
    properties/due.cpp \
    properties/dtstart.cpp \
    properties/freebusy.cpp \
    properties/transp.cpp \
    properties/durationprop.cpp \
    properties/prodid.cpp \
    properties/version.cpp \
    properties/calscale.cpp \
    properties/method.cpp \
    components/timezonerules.cpp \
    core/genericparsertemplate.cpp \
    parser.cpp \
    tests/dateparsertests.cpp \
    tests/alltests.cpp \
    tests/durationparsertests.cpp \
    tests/varioustests.cpp \
    tests/utf8validatortests.cpp

HEADERS += \
    core/genericpropertyparameter.h \
    core/genericproperty.h \
    core/genericcomponent.h \
    core/genericparser.h \
    core/stream.h \
    core/charset.h \
    core/withpos.h \
    streampos.h \
    components/vcalendar.h \
    parserexception.h \
    core/valueparser.h \
    data/date.h \
    data/time.h \
    data/datetime.h \
    data/duration.h \
    data/period.h \
    data/recurrencerule.h \
    data/utcoffset.h \
    components/vevent.h \
    components/vjournal.h \
    components/vtodo.h \
    components/vfreebusy.h \
    components/vtimezone.h \
    components/valarm.h \
    parameters/encoding.h \
    parameters/fmttype.h \
    properties/tzid.h \
    parameters/fbtype.h \
    parameters/language.h \
    parameters/member.h \
    parameters/partstat.h \
    parameters/range.h \
    parameters/related.h \
    properties/tzname.h \
    properties/tzoffsetfrom.h \
    properties/tzoffsetto.h \
    properties/tzurl.h \
    properties/attendee.h \
    properties/contact.h \
    properties/organizer.h \
    properties/recurrenceid.h \
    properties/relatedto.h \
    properties/url.h \
    properties/uid.h \
    properties/requeststatus.h \
    core/utf8validator.h \
    parameters/reltype.h \
    parameters/role.h \
    parameters/rsvp.h \
    parameters/sentby.h \
    parameters/tzid_param.h \
    parameters/value.h \
    properties/action.h \
    properties/created.h \
    properties/dtstamp.h \
    properties/exdate.h \
    properties/lastmodified.h \
    properties/rdate.h \
    properties/repeat.h \
    properties/rrule.h \
    properties/sequence.h \
    properties/trigger.h \
    parameters/altrep.h \
    parameters/calusertype.h \
    parameters/commonname.h \
    parameters/delegatedfrom.h \
    parameters/delegatedto.h \
    parameters/direntryref.h \
    properties/attach.h \
    properties/categories.h \
    properties/class.h \
    properties/comment.h \
    properties/description.h \
    properties/geo.h \
    properties/location.h \
    properties/percentcomplete.h \
    properties/priority.h \
    properties/resources.h \
    properties/status.h \
    properties/summary.h \
    properties/completed.h \
    properties/dtend.h \
    properties/due.h \
    properties/dtstart.h \
    properties/freebusy.h \
    properties/transp.h \
    properties/durationprop.h \
    properties/prodid.h \
    properties/version.h \
    properties/calscale.h \
    properties/method.h \
    components/timezonerules.h \
    core/uniqueidregistry.h \
    core/genericparsertemplate.h \
    parsertemplate.h \
    parser.h \
    tests/testreporter.h \
    tests/dateparsertests.h \
    tests/alltests.h \
    tests/durationparsertests.h \
    tests/dataparserutils.h \
    tests/varioustests.h \
    tests/utf8validatortests.h
