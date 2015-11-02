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
    data/time.cpp

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
    data/utcoffset.h
