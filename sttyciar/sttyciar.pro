######################################################################
# Automatically generated by qmake (2.01a) Thu Sep 13 14:00:50 2007
######################################################################

macx {
    error(Sttyciar does not support MacOS X at this time)
}

TEMPLATE = app
QT = core

DEPENDPATH += . src
INCLUDEPATH += . ../include

DEFINES += _REENTRANT

CONFIG += console
CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    DESTDIR = ../bin/Debug
    DEPENDPATH += ../bin/Debug
    LIBS += -L../bin/Debug
} else {
    DESTDIR = ../bin/Release
    DEPENDPATH += ../bin/Release
    LIBS += -L../bin/Release
}

LIBS += -labstractionlayer

TARGET = sttyciar

# Input
SOURCES += src/main.cpp
