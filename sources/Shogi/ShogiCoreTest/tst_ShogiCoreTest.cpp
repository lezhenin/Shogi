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
    void printBoard();
};

ShogiCoreTest::ShogiCoreTest()
{

}

void ShogiCoreTest::testCase1()
{
    Shogi game;
    game.initGame();
    std::cout << game.getBoard().getPiecesOnBoard().size() << std::endl;
    QCOMPARE(game.getBoard().getSquare(Position(5,3))->getPiece()->getType(),Rook);
}

void ShogiCoreTest::printBoard()
{
    Shogi game;
    game.initGame();
    for(int i=1; i<=9; i++)
    {
        for(int j=1; j<=9; j++)
        {
            Piece *p = game.getBoard().getSquare(Position(i,j))->getPiece();

            if (p==0) std::cout <<  "* ";
            else std:: cout << "0 ";
        }
        std::cout << std::endl;
    }
}

QTEST_APPLESS_MAIN(ShogiCoreTest)

#include "tst_ShogiCoreTest.moc"
