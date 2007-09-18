######################################################################
# Automatically generated by qmake (2.01a) Sat 15. Sep 00:24:26 2007
######################################################################

macx {
    error(Sttyciar does not support MacOS X at this time)
}

TEMPLATE = lib
QT = core

DEPENDPATH += . src
INCLUDEPATH += ../include
INCLUDEPATH += ../../resources/tbb/include

DEFINES += _REENTRANT
DEFINES += _DLL

CONFIG -= app_bundle
CONFIG += console
CONFIG += debug_and_release
CONFIG += thread

#win32:LIBS += -lmsvcp60

CONFIG(debug, debug|release) {
    DESTDIR = ../bin/Debug
    DEPENDPATH += ../bin/Debug
    LIBS += -L../bin/Debug
    LIBS += -ltbb_debug
} else {
    DESTDIR = ../bin/Release
    DEPENDPATH += ../bin/Release
    LIBS += -L../bin/Release
    LIBS += -ltbb
}

LIBS += -labstractionlayer

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

TARGET = networklogiclayer

# Input
HEADERS += ../include/abstractionlayer.hh \
           ../include/alnetworklistener.hh \
           ../include/datalinklayerpacket.hh \
           ../include/device.hh \
           ../include/ethernetiiframe.hh \
           ../include/interfaceroute.hh \
           ../include/ipv4datagram.hh \
           ../include/networklayerpacket.hh \
           ../include/networklogiclayer.hh \
           ../include/packet.hh \
           ../include/rawpacket.hh

SOURCES += src/networklogiclayer.cpp

