#include <QString>
#include <QtTest>
#include "Shogi.h"
#include <iostream>

class ShogiCoreTest : public QObject
{
    Q_OBJECT

public:
    ShogiCoreTest();

private Q_SLOTS:
    void testCase1();
};

ShogiCoreTest::ShogiCoreTest()
{

}

void ShogiCoreTest::testCase1()
{
    Shogi game;
    game.initGame();
    QCOMPARE(game.getBoard()->getSquare(Position(5,3))->getPiece()->getType(),Knight);
}

QTEST_APPLESS_MAIN(ShogiCoreTest)

#include "tst_ShogiCoreTest.moc"
