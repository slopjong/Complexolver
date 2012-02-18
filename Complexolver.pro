#-------------------------------------------------
#
# Project created by QtCreator 2012-02-17T22:47:19
#
#-------------------------------------------------

QT       += core gui svg

TARGET = Complexolver
TEMPLATE = app

include(3rd-party/qtmmlwidget-2.4_1-opensource/src/qtmmlwidget.pri)
include(3rd-party/tinyxml/tinyxml.pri)

SOURCES += src/main.cpp\
        src/mainwindow.cpp

HEADERS  += src/mainwindow.h

FORMS    += src/ui/mainwindow.ui

OBJECTS_DIR = build/objects
MOC_DIR = build/moc
UI_DIR = build/ui

## The following options could be useful at a later time

#DESTDIR = build/bin
#RESOURCES += misc.qrc

#QMAKE_CXXFLAGS += -std=gnu++0x
#QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter

#INCLUDEPATH += 3rd-party/tinyxml/include
#unix:QMAKE_RPATHDIR += lib
#unix:LIBS += -Llib -lreformath
