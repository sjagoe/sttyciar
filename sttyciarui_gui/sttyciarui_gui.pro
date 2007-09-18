######################################################################
# Automatically generated by qmake (2.01a) Tue Sep 18 10:38:31 2007
######################################################################

macx {
    error(Sttyciar does not support MacOS X at this time)
}

TEMPLATE = app

DEPENDPATH += . src
INCLUDEPATH += ../include

DEFINES += _REENTRANT

#CONFIG -= app_bundle
CONFIG += console
CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    DESTDIR = bin/Debug
    DEPENDPATH += bin/Debug
    LIBS += -L../bin/Debug
} else {
    DESTDIR = bin/Release
    DEPENDPATH += bin/Release
    LIBS += -L../bin/Release
}

win32 {
    CONFIG += dll
    CONFIG += rtti
    CONFIG += exceptions
}

TARGET = sttyciarui

# Input
FORMS += forms/main.ui

HEADERS += ../include/sttyciarui_common.hh \
           ../include/sttyciarui_gui.hh \
           ../include/sttyciarui_gui_main.hh

SOURCES += src/sttyciarui_gui.cpp \
           src/sttyciarui_gui_main.cpp