######################################################################
# Automatically generated by qmake (2.01a) Sun Sep 16 16:02:00 2007
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
}

TARGET = sttyciarui

# Input
HEADERS += ../include/sllistener.hh \
           ../include/sttyciarui_cli.hh \
           ../include/uilistener.hh \
           ../include/sttyciarui_cli_main.hh \
           ../include/sttyciarui_common.hh \
           ../include/sttyciarui_cli_statistics.hh

SOURCES += src/sttyciarui_cli.cpp \
           src/sttyciarui_cli_main.cpp \
           src/sttyciarui_cli_statistics.cpp