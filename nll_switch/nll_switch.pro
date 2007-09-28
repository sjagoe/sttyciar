######################################################################
# Automatically generated by qmake (2.01a) Fri Sep 28 11:44:14 2007
######################################################################

macx {
    error(Sttyciar does not support MacOS X at this time)
}

TEMPLATE = lib
QT = core

DEPENDPATH += . src
INCLUDEPATH += . ../include

DEFINES += _REENTRANT

CONFIG -= app_bundle
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
    #INCLUDEPATH += ../../resources/WpdPack/Include
}

INCLUDEPATH += ../../resources/tbb/include

LIBS += -labstractionlayer
LIBS += -lnetworklogiclayer

TARGET = nll_switch

# Input
HEADERS += ../include/abstractionlayer.hh \
           ../include/nllswitch.hh \
           ../include/networklogiclayer.hh \
           ../include/device.hh \
           ../include/interfaceroute.hh

SOURCES += src/nllswitch.cpp
