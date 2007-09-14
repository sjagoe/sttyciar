######################################################################
# Automatically generated by qmake (2.01a) Sat 15. Sep 00:48:15 2007
######################################################################

macx {
    error(Sttyciar does not support MacOS X at this time)
}

TEMPLATE = lib
QT = core

DEPENDPATH += . src
INCLUDEPATH += ../include

DEFINES += _REENTRANT
DEFINES += _DLL

CONFIG -= app_bundle
CONFIG += console
CONFIG += debug_and_release
CONFIG += thread

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

TARGET = abstractionlayer

# Input
HEADERS += ../include/abstractionlayer.hh \
           ../include/address.hh \
           ../include/alnetworklistener.hh \
           ../include/alstatisticslistener.hh \
           ../include/datalinklayerpacket.hh \
           ../include/device.hh \
           ../include/deviceaddress.hh \
           ../include/ethernetiiframe.hh \
           ../include/exceptions.hh \
           ../include/interfaceroute.hh \
           ../include/ipv4datagram.hh \
           ../include/networklayerpacket.hh \
           ../include/packet.hh \
           ../include/pcapthread.hh \
           ../include/rawpacket.hh


SOURCES += src/abstractionlayer.cpp \
           src/address.cpp \
           src/device.cpp \
           src/deviceaddress.cpp \
           src/ethernetiiframe.cpp \
           src/exceptions.cpp \
           src/interfaceroute.cpp \
           src/ipv4datagram.cpp \
           src/pcapthread.cpp \
           src/rawpacket.cpp
