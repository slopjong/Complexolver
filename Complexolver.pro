#-------------------------------------------------
#
# Project created by QtCreator 2012-02-17T22:47:19
#
#-------------------------------------------------

QT       += core gui svg

TARGET = Complexolver
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp

HEADERS  += src/mainwindow.h

FORMS    += src/ui/mainwindow.ui


#DESTDIR = build/bin
OBJECTS_DIR = build/objects
MOC_DIR = build/moc

UI_DIR = build/ui

#RESOURCES += misc.qrc

#QMAKE_CXXFLAGS += -std=gnu++0x
#QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter

unix:INCLUDEPATH += include
unix:QMAKE_RPATHDIR += lib
unix:LIBS += -Llib -lreformath

