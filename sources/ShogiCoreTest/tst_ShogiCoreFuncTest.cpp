#include <QString>
#include <QtTest>
#include "../ShogiCore/Model/BoardMemento.h"
#include "../ShogiCore/Shogi.h"
#include <iostream>

class ShogiCoreFuncTest : public QObject
{
    Q_OBJECT

public:
    ShogiCoreFuncTest();

private Q_SLOTS:
    void gameInitTest();
    void pickAndMoveTest();
    void undoAndRedoTest();
    void promoteTest();
    void getGameSitutatuinTest();
    void dropTest();


private:
    Shogi game;
    void printBoard();
};

ShogiCoreFuncTest::ShogiCoreFuncTest()
{

}

void ShogiCoreFuncTest::printBoard()
{

    for(int i=1; i<=9; i++)
    {
        for(int j=9; j>=1; j--)
        {
            Piece *p = game.getBoard().getPiece(Position(i,j));

            if (p==0) std::cout <<  "* ";
            else std:: cout << "0 ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ShogiCoreFuncTest::gameInitTest()
{
    game.initGame();
    AbstractBoard &board = game.getBoard();
    for(int i = 1; i<=9; i++)
    {
     QVERIFY(board.getPiece(Position(9,i)) != nullptr);
     QVERIFY(board.getPiece(Position(7,i)) != nullptr);
     QVERIFY(board.getPiece(Position(1,i)) != nullptr);
     QVERIFY(board.getPiece(Position(3,i)) != nullptr);
    }
    QVERIFY(board.getPiece(Position(8,8)) != nullptr);
    QVERIFY(board.getPiece(Position(8,2)) != nullptr);
    QVERIFY(board.getPiece(Position(2,2)) != nullptr);
    QVERIFY(board.getPiece(Position(2,8)) != nullptr);
    QCOMPARE((int)board.getAllPieces().size(),40);
    QCOMPARE((int)board.getPiecesOnBoard().size(),40);
    QCOMPARE((int)board.getCapturedPieces(Sente).size(),0);
    QCOMPARE((int)board.getCapturedPieces(Gote).size(),0);
    printBoard();
}

void ShogiCoreFuncTest::pickAndMoveTest()
{
    QVERIFY_EXCEPTION_THROWN(game.pickPiece(Position(3,2)), std::exception);
    QVERIFY_EXCEPTION_THROWN(game.pickPiece(Position(5,5)), std::exception);
    game.pickPiece(Position(7,2));
    QVERIFY_EXCEPTION_THROWN(game.movePiece(Position(5,2)), std::exception);
    game.movePiece(Position(6,2));
    QVERIFY(game.getBoard().getPiece(Position(7,2)) == nullptr);
    QVERIFY(game.getBoard().getPiece(Position(6,2)) != nullptr);
    printBoard();
    game.pickPiece(Position(3,2));
    game.movePiece(Position(4,2));
    QVERIFY(game.getBoard().getPiece(Position(3,2)) == nullptr);
    QVERIFY(game.getBoard().getPiece(Position(4,2)) != nullptr);
    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));
    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));
    QCOMPARE((int)game.getBoard().getAllPieces().size(),40);
    QCOMPARE((int)game.getBoard().getPiecesOnBoard().size(),39);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Sente).size(),0);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Gote).size(),1);
    QCOMPARE((*game.getBoard().getCapturedPieces(Gote).begin())->getPlayer(),Gote);
    QCOMPARE((*game.getBoard().getCapturedPieces(Gote).begin())->getType(),Pawn);
    printBoard();



}
void ShogiCoreFuncTest::undoAndRedoTest()
{
    game.pickPiece(Position(9,5));
    game.movePiece(Position(8,5));
    printBoard();
    QVERIFY(game.getBoard().getPiece(Position(9,5)) == nullptr);
    QVERIFY(game.getBoard().getPiece(Position(8,5)) != nullptr);
    game.undo();
    printBoard();
    QVERIFY(game.getBoard().getPiece(Position(9,5)) != nullptr);
    QVERIFY(game.getBoard().getPiece(Position(8,5)) == nullptr);
    game.redo();
    printBoard();
    QVERIFY(game.getBoard().getPiece(Position(9,5)) == nullptr);
    QVERIFY(game.getBoard().getPiece(Position(8,5)) != nullptr);
    game.pickPiece(Position(5,2));
    game.movePiece(Position(6,2));
    game.pickPiece(Position(9,6));
    game.movePiece(Position(8,6));
    printBoard();
}

void ShogiCoreFuncTest::promoteTest()
{
    QVERIFY_EXCEPTION_THROWN(game.promotePiece(Position(6,2)),std::exception);
    game.pickPiece(Position(6,2));
    game.movePiece(Position(7,2));
    game.promotePiece(Position(7,2));
    QCOMPARE(game.getBoard().getPiece(Position(7,2))->getType(), PromotedPawn);
}

void ShogiCoreFuncTest::getGameSitutatuinTest()
{
    QCOMPARE((int)game.getGameSituation().size(),1);
    QVERIFY(!game.getGameSituation().front()->isEndOfGame());
    QCOMPARE(game.getGameSituation().front()->getMessage(), std::string("You can promote piece."));
    game.getGameSituation().pop();
    QVERIFY(game.getGameSituation().empty());
}
void ShogiCoreFuncTest::dropTest()
{
    game.pickPiece(Position(8,2));
    game.movePiece(Position(7,2));
    QCOMPARE((int)game.getBoard().getPiecesOnBoard().size(),38);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Sente).size(),1);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Gote).size(),1);
    QVERIFY_EXCEPTION_THROWN(game.dropPiece(Pawn,Position(5,3)),std::exception);
    QVERIFY_EXCEPTION_THROWN(game.dropPiece(Pawn,Position(7,2)),std::exception);
    game.dropPiece(Pawn,Position(5,2));
    QVERIFY(game.getBoard().getPiece(Position(5,2)) != nullptr);
    QCOMPARE((int)game.getBoard().getPiecesOnBoard().size(),39);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Sente).size(),1);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Gote).size(),0);
    printBoard();
}




QTEST_APPLESS_MAIN(ShogiCoreFuncTest)

#include "tst_ShogiCoreFuncTest.moc"

