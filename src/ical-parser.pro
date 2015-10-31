TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
QMAKE_CXXFLAGS_DEBUG += -DDEBUG

SOURCES += main.cpp \
    core/genericparser.cpp \
    components/vcalendar.cpp

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
    parserexception.h
