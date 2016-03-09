#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T17:55:48
#
#-------------------------------------------------

QT       -= core gui
QMAKE_CXXFLAGS += -std=c++11
TARGET = ShogiCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=  ShogiAPI.cpp \
    Position.cpp \
    Piece.cpp \
    Square.cpp \
    Board.cpp \
    Shogi.cpp

HEADERS +=  ShogiAPI.h \
    Position.h \
    constants.h \
    Piece.h \
    Square.h \
    enumirations.h \
    Board.h \
    Shogi.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
