#include <QString>
#include <QtTest>
#include "../ShogiCore/Shogi.h"
#include "../ShogiCore/Model/BoardMemento.h"
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
    void mementoTest();
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
    std::cout << std::endl;
    std::cout << "Pieces on board: " << game.getBoard().getPiecesOnBoard().size() << std::endl;
}

void ShogiCoreTest::gameInitTest()
{
    game.initGame();
    QCOMPARE(game.getBoard().getPiece(Position(5,3))->getType(),Rook);
    printBoard();
}

void ShogiCoreTest::pickAndMoveTest()
{
    std::cout << "Pieces on board: " << game.getBoard().getPiecesOnBoard().size() << std::endl;
    game.pickPiece(Position(5,3));
    game.movePiece(Position(3,8));
    QVERIFY(game.getBoard().getPiece(Position(5,3)) == nullptr);
    QVERIFY(game.getBoard().getPiece(Position(3,8)) != nullptr);
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
    QVERIFY(game.getBoard().getPiece(Position(2,2)) != nullptr);
    printBoard();
    std::cout << "Pieces on board: " << game.getBoard().getPiecesOnBoard().size() << std::endl;
}

void ShogiCoreTest::mementoTest()
{
    BoardMemento bm(&game.getBoard());
    game.getBoard().removePiece(Position(2,2));
    printBoard();
    bm.restore();
    printBoard();
}


QTEST_APPLESS_MAIN(ShogiCoreTest)

#include "tst_ShogiCoreTest.moc"

