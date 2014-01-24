#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T14:37:19
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tron
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tron.cpp \
    player.cpp \
    tronwidget.cpp

HEADERS  += mainwindow.h \
    tron.h \
    player.h \
    tronwidget.h \
    clamp.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.md \
    LICENSE.txt
