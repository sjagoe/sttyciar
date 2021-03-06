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
DEFINES += HAVE_REMOTE

CONFIG -= app_bundle
#CONFIG += console
CONFIG += debug_and_release
CONFIG += thread

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

TARGET = abstractionlayer

# Input
HEADERS += ../include/abstractionlayer.hh \
           ../include/address.hh \
           ../include/alnetworklistener.hh \
           ../include/alstatisticslistener.hh \
           ../include/datalinklayerpacket.hh \
           ../include/defaultstatisticslayer.hh \
           ../include/device.hh \
           ../include/deviceaddress.hh \
           ../include/ethernetiiframe.hh \
           ../include/exceptions.hh \
           ../include/interfaceroute.hh \
           ../include/ipv4datagram.hh \
           ../include/networklayerpacket.hh \
           ../include/packet.hh \
           ../include/pcapreceivethread.hh \
           ../include/rawpacket.hh \
           ../include/packetaccess.hh \
           ../include/pcapsendthread.hh


SOURCES += src/abstractionlayer.cpp \
           src/pcapsendthread.cpp \
           src/address.cpp \
           src/device.cpp \
           src/deviceaddress.cpp \
           src/ethernetiiframe.cpp \
           src/exceptions.cpp \
           src/interfaceroute.cpp \
           src/ipv4datagram.cpp \
           src/pcapreceivethread.cpp \
           src/rawpacket.cpp
