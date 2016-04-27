#include <QString>
#include <QtTest>
#include "../ShogiCore/Model/BoardMemento.h"
#include "../ShogiCore/API/Shogi.h"
#include "../ShogiCore/SaveAndLoad/Simple/SimpleSaveManager.h"
#include <iostream>

using namespace shogi;

class ShogiCoreFuncTest : public QObject
{
    Q_OBJECT

public:
    ShogiCoreFuncTest();

private Q_SLOTS:
    void initTestCase();
    void pickTest();
    void moveTest();
    void undoAndRedoTest();
    void promoteTest();
    void getGameSitutatuinTest();
    void dropTest();
    void saveTest();
    void loadTest();


private:

};

ShogiCoreFuncTest::ShogiCoreFuncTest()
{

}


void ShogiCoreFuncTest::initTestCase()
{
    Shogi game;
    game.load();
    QCOMPARE(game.getCurrentPlayer(),Player(Sente));

    AbstractBoard &board = game.getBoard();

    Piece *pieceForCompare = new Piece(Pawn,Sente);
    Piece *pieceForCompare1 = new Piece(Pawn,Gote);

    for(int i = 1; i<=9; i++)
    {
     QVERIFY(board.getPiece(Position(9,i)) != nullptr);
     QVERIFY(board.getPiece(Position(7,i)) != nullptr);
     QVERIFY(board.getPiece(Position(7,i))->equals(pieceForCompare));
     QVERIFY(board.getPiece(Position(1,i)) != nullptr);
     QVERIFY(board.getPiece(Position(3,i)) != nullptr);
     QVERIFY(board.getPiece(Position(3,i))->equals(pieceForCompare1));
    }

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(Lance,Sente);
    pieceForCompare1 = new Piece(Lance,Gote);
    QVERIFY(board.getPiece(Position(9,1))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(9,9))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(1,1))->equals(pieceForCompare1));
    QVERIFY(board.getPiece(Position(1,9))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(Knight,Sente);
    pieceForCompare1 = new Piece(Knight,Gote);
    QVERIFY(board.getPiece(Position(9,2))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(9,8))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(1,2))->equals(pieceForCompare1));
    QVERIFY(board.getPiece(Position(1,8))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(SilverGeneral,Sente);
    pieceForCompare1 = new Piece(SilverGeneral,Gote);
    QVERIFY(board.getPiece(Position(9,3))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(9,7))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(1,3))->equals(pieceForCompare1));
    QVERIFY(board.getPiece(Position(1,7))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(GoldGeneral,Sente);
    pieceForCompare1 = new Piece(GoldGeneral,Gote);
    QVERIFY(board.getPiece(Position(9,4))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(9,6))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(1,4))->equals(pieceForCompare1));
    QVERIFY(board.getPiece(Position(1,6))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(King,Sente);
    pieceForCompare1 = new Piece(King,Gote);
    QVERIFY(board.getPiece(Position(9,5))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(1,5))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(Bishop,Sente);
    pieceForCompare1 = new Piece(Bishop,Gote);

    QVERIFY(board.getPiece(Position(8,8)) != nullptr);
    QVERIFY(board.getPiece(Position(8,8))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(2,2)) != nullptr);
    QVERIFY(board.getPiece(Position(2,2))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;
    pieceForCompare = new Piece(Rook,Sente);
    pieceForCompare1 = new Piece(Rook,Gote);

    QVERIFY(board.getPiece(Position(8,2)) != nullptr);
    QVERIFY(board.getPiece(Position(8,2))->equals(pieceForCompare));
    QVERIFY(board.getPiece(Position(2,8)) != nullptr);
    QVERIFY(board.getPiece(Position(2,8))->equals(pieceForCompare1));

    delete pieceForCompare;
    delete pieceForCompare1;

    QCOMPARE((int)board.getAllPieces().size(),40);
    QCOMPARE((int)board.getPiecesOnBoard().size(),40);
    QCOMPARE((int)board.getCapturedPieces(Sente).size(),0);
    QCOMPARE((int)board.getCapturedPieces(Gote).size(),0);
}


void ShogiCoreFuncTest::pickTest()
{
    Shogi game;
    game.load();
    QVERIFY_EXCEPTION_THROWN(game.pickPiece(Position(3,2)), BadPickException);
    QVERIFY_EXCEPTION_THROWN(game.pickPiece(Position(5,5)), BadPickException);
    Position samplePosition(7,2);
    game.pickPiece(samplePosition);
    QCOMPARE(game.getPickedPiece(),game.getBoard().getPiece(samplePosition));
    game.unPickPiece();
    Piece *samplePiece = nullptr;
    QCOMPARE(game.getPickedPiece(), samplePiece);

}

void ShogiCoreFuncTest::moveTest()
{
    Shogi game;
    game.load();
    Position source(7,2);
    Position destination(6,2);
    game.pickPiece(source);
    QVERIFY_EXCEPTION_THROWN(game.movePiece(Position(5,2)), BadMoveException);
    game.movePiece(destination);
    QVERIFY(game.getBoard().getPiece(source) == nullptr);
    QVERIFY(game.getBoard().getPiece(destination) != nullptr);
    QCOMPARE(game.getCurrentPlayer(),Player(Gote));

    source = Position(3,2);
    destination = Position(4,2);
    game.pickPiece(source);
    game.movePiece(destination);
    QVERIFY(game.getBoard().getPiece(source) == nullptr);
    QVERIFY(game.getBoard().getPiece(destination) != nullptr);
    QCOMPARE(game.getCurrentPlayer(),Player(Sente));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));

    QCOMPARE((int)game.getBoard().getAllPieces().size(),40);
    QCOMPARE((int)game.getBoard().getPiecesOnBoard().size(),39);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Sente).size(),0);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Gote).size(),1);
    QVERIFY((*game.getBoard().getCapturedPieces(Gote).begin())->getPlayer() == Gote);
    QVERIFY((*game.getBoard().getCapturedPieces(Gote).begin())->getType() == Pawn);
}

void ShogiCoreFuncTest::undoAndRedoTest()
{
    Shogi game;
    game.load();

    QCOMPARE(game.getCurrentPlayer(),Player(Sente));
    game.pickPiece(Position(7,3));
    game.movePiece(Position(6,3));
    QCOMPARE(game.getCurrentPlayer(),Player(Gote));

    game.undo();
    QVERIFY(game.getBoard().getPiece(Position(7,3)) != nullptr);
    QVERIFY(game.getBoard().getPiece(Position(6,3)) == nullptr);
    QCOMPARE(game.getCurrentPlayer(),Player(Sente));

    game.redo();
    QVERIFY(game.getBoard().getPiece(Position(7,3)) == nullptr);
    QVERIFY(game.getBoard().getPiece(Position(6,3)) != nullptr);
    QCOMPARE(game.getCurrentPlayer(),Player(Gote));

    game.undo();
    QVERIFY(game.getBoard().getPiece(Position(7,3)) != nullptr);
    QVERIFY(game.getBoard().getPiece(Position(6,3)) == nullptr);
    QCOMPARE(game.getCurrentPlayer(),Player(Sente));
}

void ShogiCoreFuncTest::promoteTest()
{
    Shogi game;
    game.load();
    QVERIFY_EXCEPTION_THROWN(game.promotePiece(Position(7,2)),BadPromoteException);

    game.pickPiece(Position(7,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(3,2));
    game.movePiece(Position(4,2));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(7,3));
    game.movePiece(Position(6,3));

    game.pickPiece(Position(5,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(6,3));
    game.movePiece(Position(5,3));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(7,2));

    game.promotePiece(Position(7,2));
    QCOMPARE(game.getBoard().getPiece(Position(7,2))->getType(), PromotedPawn);
}

void ShogiCoreFuncTest::getGameSitutatuinTest()
{
    Shogi game;
    game.load();

    game.pickPiece(Position(7,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(3,2));
    game.movePiece(Position(4,2));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(7,3));
    game.movePiece(Position(6,3));

    game.pickPiece(Position(5,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(6,3));
    game.movePiece(Position(5,3));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(7,2));

    QCOMPARE((int)game.getGameSituation().size(),1);
    QVERIFY(!game.getGameSituation().front()->isEndOfGame());
    QCOMPARE(game.getGameSituation().front()->getMessage(), std::string("You can promote piece."));
    game.getGameSituation().pop();
    QVERIFY(game.getGameSituation().empty());
}

void ShogiCoreFuncTest::dropTest()
{
    Shogi game;
    game.load();

    game.pickPiece(Position(7,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(3,2));
    game.movePiece(Position(4,2));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(8,2));
    game.movePiece(Position(5,2));

    QCOMPARE((int)game.getBoard().getPiecesOnBoard().size(),38);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Sente).size(),1);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Gote).size(),1);

    QVERIFY_EXCEPTION_THROWN(game.dropPiece(Pawn,Position(5,3)), BadDropException);
    QVERIFY_EXCEPTION_THROWN(game.dropPiece(Lance,Position(6,2)), BadDropException);

    game.dropPiece(Pawn,Position(7,2));

    QVERIFY(game.getBoard().getPiece(Position(7,2)) != nullptr);
    QCOMPARE((int)game.getBoard().getPiecesOnBoard().size(),39);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Sente).size(),1);
    QCOMPARE((int)game.getBoard().getCapturedPieces(Gote).size(),0);
}

void ShogiCoreFuncTest::saveTest()
{
    Shogi game;
    game.load();

    game.pickPiece(Position(7,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(3,2));
    game.movePiece(Position(4,2));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(8,2));
    game.movePiece(Position(5,2));

    SimpleSaveManager *saveManager = new SimpleSaveManager();
    game.save(saveManager);
    const SimpleSave *save = saveManager->getSimpleSave();

    QCOMPARE(save->currentPlayer, Player(Gote));
    QCOMPARE((int)save->onBoard.size(), 38);
    QCOMPARE((int)save->goteCaptured.size(), 1);
    QCOMPARE((int)save->senteCaptured.size(), 1);

    delete saveManager;

}

void ShogiCoreFuncTest::loadTest()
{
    Shogi game;
    Shogi game1;
    game.load();

    game.pickPiece(Position(7,2));
    game.movePiece(Position(6,2));

    game.pickPiece(Position(3,2));
    game.movePiece(Position(4,2));

    game.pickPiece(Position(6,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(4,2));
    game.movePiece(Position(5,2));

    game.pickPiece(Position(8,2));
    game.movePiece(Position(5,2));

    SimpleSaveManager *saveManager = new SimpleSaveManager();
    game.save(saveManager);
    game1.load(saveManager);

    AbstractBoard &board = game.getBoard();
    AbstractBoard &board1 = game1.getBoard();
    for(int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            Position position(i, j);
            Piece *samplePiece = board.getPiece(position);
            Piece *samplePiece1 = board1.getPiece(position);

            if(samplePiece == nullptr)
            {
                QCOMPARE(samplePiece,samplePiece1);
            }
            else
            {
                QVERIFY(board.getPiece(position)->equals(
                        board1.getPiece(position)));
            }
        }
    }
    QCOMPARE(board.getCapturedPieces(Sente).size(), board1.getCapturedPieces(Sente).size());
    QCOMPARE(board.getCapturedPieces(Gote).size(), board1.getCapturedPieces(Gote).size());

    delete saveManager;
}


QTEST_APPLESS_MAIN(ShogiCoreFuncTest)

#include "tst_ShogiCoreFuncTest.moc"

