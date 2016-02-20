#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T02:03:31
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = GameCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    GameAPI.cpp

HEADERS += \
    GameAPI.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
