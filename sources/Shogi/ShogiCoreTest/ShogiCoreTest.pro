#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:17:09
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_ShogiCoreTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_ShogiCoreTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ShogiCore/release/ -lShogiCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ShogiCore/debug/ -lShogiCore
else:unix: LIBS += -L$$OUT_PWD/../ShogiCore/ -lShogiCore

INCLUDEPATH += $$PWD/../ShogiCore
DEPENDPATH += $$PWD/../ShogiCore

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ShogiCore/release/libShogiCore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ShogiCore/debug/libShogiCore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ShogiCore/release/ShogiCore.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ShogiCore/debug/ShogiCore.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ShogiCore/libShogiCore.a
