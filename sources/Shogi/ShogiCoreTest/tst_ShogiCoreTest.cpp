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
    void gameInitTest();
    void pickAndMoveTest();
    void promoteTest();
    void dropTest();
private:
    Shogi game;
    void printBoard();
};

ShogiCoreTest::ShogiCoreTest()
{

}

void ShogiCoreTest::printBoard()
{

    for(int i=1; i<=9; i++)
    {
        for(int j=1; j<=9; j++)
        {
            Piece *p = game.getBoard().getPiece(Position(i,j));

            if (p==0) std::cout <<  "* ";
            else std:: cout << "0 ";
        }
        std::cout << std::endl;
    }
}

void ShogiCoreTest::gameInitTest()
{
    game.initGame();
    std::cout << "Pieces on board: " << game.getBoard().getPiecesOnBoard().size() << std::endl;
    QCOMPARE(game.getBoard().getPiece(Position(5,3))->getType(),Rook);
    printBoard();
}

void ShogiCoreTest::pickAndMoveTest()
{

    game.pickPiece(Position(5,3));
    game.movePiece(Position(3,8));
    printBoard();
}

void ShogiCoreTest::promoteTest()
{   PieceType pt = game.getBoard().getPiece(Position(3,8))->getType();
    game.promotePiece(Position(3,8));
    QVERIFY(game.getBoard().getPiece(Position(3,8))->getType()!=pt);

}

void ShogiCoreTest::dropTest()
{
    game.dropPiece(King,Position(2,2));
    printBoard();
}



QTEST_APPLESS_MAIN(ShogiCoreTest)

#include "tst_ShogiCoreTest.moc"
