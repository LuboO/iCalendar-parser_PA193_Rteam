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
    properties/ianaprop.cpp \
    properties/nonstdprop.cpp \
    properties/requeststatus.cpp \
    core/utf8validator.cpp

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
    properties/ianaprop.h \
    properties/nonstdprop.h \
    properties/requeststatus.h \
    core/utf8validator.h
