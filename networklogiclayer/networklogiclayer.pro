######################################################################
# Automatically generated by qmake (2.01a) Thu 13. Sep 21:06:53 2007
######################################################################

macx {
    error(Sttyciar does not support MacOS X at this time)
}

TEMPLATE = lib
QT = core

DEPENDPATH += . src
INCLUDEPATH += ../include

DEFINES += _REENTRANT

CONFIG -= app_bundle
CONFIG += console
CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    DESTDIR = ../bin/Debug
    DEPENDPATH += ../bin/Debug
} else {
    DESTDIR = ../bin/Release
    DEPENDPATH += ../bin/Release
}

win32 {
    CONFIG += dll
    CONFIG += rtti
    CONFIG += exceptions
    INCLUDEPATH += ../../resources/WpdPack/Include
}

TARGET = networklogiclayer

# Input
SOURCES += src/networklogiclayer.cpp
