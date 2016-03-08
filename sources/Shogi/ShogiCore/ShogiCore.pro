#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T17:55:48
#
#-------------------------------------------------

QT       -= core gui

TARGET = ShogiCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=  ShogiAPI.cpp \
    Position.cpp \
    Piece.cpp \
    Square.cpp \
    Board.cpp

HEADERS +=  ShogiAPI.h \
    Position.h \
    constants.h \
    Piece.h \
    Square.h \
    enumirations.h \
    Board.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
