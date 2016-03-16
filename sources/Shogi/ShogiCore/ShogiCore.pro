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
    Shogi.cpp \
    Model/Board.cpp \
    Model/Piece.cpp \
    Model/Position.cpp \
    Model/Square.cpp \
    Model/SquareIsEmptyException.cpp

HEADERS +=  ShogiAPI.h \
    constants.h \
    enumirations.h \
    Model/Board.h \
    Model/BoardInterface.h \
    Model/Piece.h \
    Model/Position.h \
    Model/Square.h \
    Model/SquareIsEmptyException.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
