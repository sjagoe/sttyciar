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
DEFINES += _DLL

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

win32 {
    CONFIG += dll
    CONFIG += rtti
    CONFIG += exceptions
    INCLUDEPATH += ../../resources/WpdPack/Include
    LIBS += -L../../resources/WpdPack/Lib
    LIBS += -lpacket
    LIBS += -lwpcap
} else {
    LIBS += -lpcap
}

INCLUDEPATH += ../../resources/tbb/include

LIBS += -labstractionlayer
LIBS += -lnetworklogiclayer
LIBS += -lnll_hub

TARGET = sttyciar

# Input
SOURCES += src/main.cpp
