#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T17:53:26
#
#-------------------------------------------------

QT       -= core gui

TARGET = ShogiAI
TEMPLATE = lib
CONFIG += staticlib

SOURCES += shogiai.cpp

HEADERS += shogiai.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
