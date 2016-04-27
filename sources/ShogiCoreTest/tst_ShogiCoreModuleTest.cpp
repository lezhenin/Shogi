#include <QString>
#include <QtTest>
#include "../ShogiCore/Model/BoardMemento.h"
#include "../ShogiCore/GameLogic/GameLogic.h"
#include "../ShogiCore/SaveAndLoad/GameLoader.h"
#include "../ShogiCore/Model/Exceptions/BadPositionException.h"
#include "../ShogiCore/SaveAndLoad/Simple/SimpleSave.h"
#include "../ShogiCore/SaveAndLoad/Simple/SimpleSaveManager.h"
#include "../ShogiCore/SaveAndLoad/GameSaver.h"
#include "../ShogiCore/SaveAndLoad/JSON/JSONSaveManager.h"
#include "../ShogiCore/Model/Exceptions/PieceIsNotOnBoardException.h"

using namespace shogi;

class ShogiCoreModuleTest : public QObject
{
Q_OBJECT

public:
    ShogiCoreModuleTest();

private Q_SLOTS:

    void boardTest();
    void pieceTest();
    void mementoTest();
    void gameLogicTest();
    void gameLoaderTest();
    void gameSaverTest();
    void JSONSaveManagerTest();


private:
};

ShogiCoreModuleTest::ShogiCoreModuleTest()
{

}
void ShogiCoreModuleTest::mementoTest()
{
    Piece p1 = Piece(Rook, Sente);
    Piece p2 = Piece(King, Gote);
    Piece p3 = Piece(Pawn, Gote);
    Piece p4 = Piece(Knight, Sente);

    AbstractBoard *board = new Board();

    board->setPiece(&p1, Position(2, 2));
    board->setPiece(&p2, Position(4, 5));

    board->getCapturedPieces(Gote).push_back(&p3);
    board->getCapturedPieces(Sente).push_back(&p4);

    AbstractBoardMemento *bm = board->getMemento();

    board->removePiece(Position(2, 2));
    board->removePiece(Position(4, 5));

    board->getCapturedPieces(Gote).clear();
    board->getCapturedPieces(Sente).clear();

    QVERIFY(board->getPiece(Position(2, 2)) == nullptr);
    QVERIFY(board->getPiece(Position(4, 5)) == nullptr);
    QCOMPARE((int)board->getPiecesOnBoard().size(),0);

    board->setMemento(bm);
    QVERIFY(board->getPiece(Position(2, 2)) == &p1);
    QVERIFY(board->getPiece(Position(4, 5)) == &p2);
    QCOMPARE((int)board->getPiecesOnBoard().size(),2);
    QCOMPARE((int)board->getCapturedPieces(Sente).size(),1);
    QCOMPARE((int)board->getCapturedPieces(Gote).size(),1);

    delete bm;
    delete board;
}

void ShogiCoreModuleTest::gameLogicTest()
{
    AbstractBoard *board = new Board();

    Piece p1 = Piece(Rook, Sente);
    Piece p2 = Piece(King, Gote);
    Piece p3 = Piece(Rook, Gote);
    Piece p4 = Piece(King, Sente);
    Piece p5 = Piece(Rook, Sente);
    Piece p6 = Piece(Pawn, Gote);

    GameLogic gameLogic(board);

    board->setPiece(&p1, Position(2, 2));
    board->setPiece(&p2, Position(2, 4));
    board->setPiece(&p3, Position(8, 1));
    board->setPiece(&p4, Position(3, 1));
    QVERIFY(gameLogic.checkShah(Sente));
    QVERIFY(gameLogic.checkShah(Gote));
    QVERIFY(gameLogic.checkMove(&p1, Position(2, 4)));
    QVERIFY(gameLogic.checkMove(&p2, Position(3, 5)));

    board->removePiece(Position(2, 4));
    board->setPiece(&p2, Position(9, 9));
    board->removePiece(Position(3, 1));
    board->setPiece(&p4, Position(8, 8));
    board->removePiece(Position(2, 2));

    QVERIFY(!gameLogic.checkDrop(&p1, Position(8, 3)));
    QVERIFY(gameLogic.checkDrop(&p1, Position(6, 3)));

    board->setPiece(&p1, Position(9, 2));
    QVERIFY(!gameLogic.checkMate(Gote));

    board->setPiece(&p5, Position(8, 3));
    QVERIFY(gameLogic.checkMate(Gote));
    QVERIFY(!gameLogic.checkDrop(&p6, Position(1, 5)));
    QVERIFY(gameLogic.checkDrop(&p6, Position(9, 5)));

    board->setPiece(&p6,Position(1,5));
    QVERIFY(!gameLogic.checkDrop(&p6, Position(7,5)));

    delete board;
}

void ShogiCoreModuleTest::gameLoaderTest()
{
    SimpleSave save;
    save.currentPlayer = Gote;
    save.onBoard.push_back(Block(Pawn, Sente, Position(1, 2)));
    save.onBoard.push_back(Block(PromotedLance, Gote, Position(5, 5)));
    save.goteCaptured.push_back(Knight);
    save.senteCaptured.push_back(GoldGeneral);

    Player player;
    AbstractBoard *board = new Board();
    GameLoader gameLoader;
    SimpleSaveManager *saveManager = new SimpleSaveManager(save);
    gameLoader.loadGame(saveManager, *board, &player);

    QCOMPARE(player, Player(Gote));
    QCOMPARE(board->getPiece(Position(1, 2))->getType(), Pawn);
    QCOMPARE(board->getPiece(Position(1, 2))->getPlayer(), Player(Sente));
    QCOMPARE(board->getPiece(Position(5, 5))->getType(), PromotedLance);
    QCOMPARE(board->getPiece(Position(5, 5))->getPlayer(), Player(Gote));

    QCOMPARE((int)board->getPiecesOnBoard().size(), 2);
    QCOMPARE((*board->getCapturedPieces(Gote).begin())->getPlayer(), Player(Gote));
    QCOMPARE((*board->getCapturedPieces(Gote).begin())->getType(), Knight);
    QCOMPARE((*board->getCapturedPieces(Sente).begin())->getPlayer(), Player(Sente));
    QCOMPARE((*board->getCapturedPieces(Sente).begin())->getType(), GoldGeneral);

    delete saveManager;
    delete board;
}

void ShogiCoreModuleTest::boardTest()
{
    AbstractBoard *board = new Board();
    Piece samplePiece(GoldGeneral, Sente);

    Position position(-5,5);
    QVERIFY_EXCEPTION_THROWN(board->setPiece(&samplePiece, position),BadPositionException);

    position = Position(5, 0);
    QVERIFY_EXCEPTION_THROWN(board->setPiece(&samplePiece, position),BadPositionException);

    position = Position(AbstractBoard::BOARD_HEIGHT + 1, 3);
    QVERIFY_EXCEPTION_THROWN(board->setPiece(&samplePiece, position),BadPositionException);

    position = Position(5, 5);
    board->setPiece(&samplePiece,position);

    QCOMPARE(board->getPiece(position), &samplePiece);
    QCOMPARE(*board->getPiecesOnBoard().begin(), &samplePiece);

    board->removePiece(position);
    QVERIFY(board->getPiece(position) == nullptr);
    QVERIFY(board->getPiecesOnBoard().empty());

    delete board;
}

void ShogiCoreModuleTest::pieceTest()
{
    Piece piece(Lance, Sente);
    Piece piece1(Lance, Sente);
    Piece piece2(Lance, Gote);
    Piece piece3(King, Sente);
    Piece piece4(PromotedBishop, Gote);

    QVERIFY_EXCEPTION_THROWN(piece.getPosition(), PieceIsNotOnBoardException);

    QVERIFY(piece.equals(&piece1));
    QVERIFY(!piece.equals(&piece2));
    QVERIFY(!piece.equals(&piece3));

    QVERIFY(piece.canBePromoted());
    QVERIFY(!piece3.canBePromoted());

    QVERIFY(!piece1.wasPromoted());
    QVERIFY(piece4.wasPromoted());

    piece.promote();
    QVERIFY(piece.wasPromoted());
    QCOMPARE(piece.getType(), PromotedLance);

    piece.unPromote();
    QVERIFY(!piece.wasPromoted());
    QCOMPARE(piece.getType(), Lance);
}

void ShogiCoreModuleTest::gameSaverTest()
{
    Piece piece(Lance, Sente);
    Piece piece1(Knight, Sente);
    Piece piece2(Lance, Gote);
    Piece piece3(King, Sente);
    Piece piece4(PromotedBishop, Gote);

    AbstractBoard *board = new Board();
    Player player = Gote;

    board->setPiece(&piece, Position(5, 5));
    board->setPiece(&piece1, Position(4, 6));
    board->setPiece(&piece4, Position(1, 9));

    board->getCapturedPieces(Sente).push_back(&piece3);
    board->getCapturedPieces(Gote).push_back(&piece2);

    GameSaver gameSaver;
    SimpleSaveManager *saveManager = new SimpleSaveManager();
    gameSaver.saveGame(saveManager, *board, &player);

   const SimpleSave *save = saveManager->getSimpleSave();

    auto iterator = std::find(save->onBoard.begin(),
                              save->onBoard.end(),
                              Block(piece.getType(), piece.getPlayer(), piece.getPosition()));

    QVERIFY(iterator != save->onBoard.end());

    iterator = std::find(save->onBoard.begin(),
                              save->onBoard.end(),
                              Block(piece1.getType(), piece1.getPlayer(), piece1.getPosition()));

    QVERIFY(iterator != save->onBoard.end());

    iterator = std::find(save->onBoard.begin(),
                              save->onBoard.end(),
                              Block(piece4.getType(), piece4.getPlayer(), piece4.getPosition()));

    QVERIFY(iterator != save->onBoard.end());

    QCOMPARE(*save->goteCaptured.begin(), piece2.getType());
    QCOMPARE(*save->senteCaptured.begin(), piece3.getType());

    delete board;
    delete saveManager;
}

void ShogiCoreModuleTest::JSONSaveManagerTest()
{
    Piece piece(Lance, Sente);
    Piece piece1(Knight, Sente);
    Piece piece2(Lance, Gote);
    Piece piece3(King, Sente);
    Piece piece4(PromotedBishop, Gote);

    AbstractBoard *board = new Board();
    Player player = Gote;

    board->setPiece(&piece, Position(5, 5));
    board->setPiece(&piece1, Position(4, 6));
    board->setPiece(&piece4, Position(1, 9));

    board->getCapturedPieces(Sente).push_back(&piece3);
    board->getCapturedPieces(Gote).push_back(&piece2);

    JSONSaveManager * saveManager = new JSONSaveManager();
    GameSaver saver;
    saver.saveGame(saveManager, *board, &player);
    std::string save = saveManager->getJSONString();
    delete saveManager;

    Player player1;
    AbstractBoard *board1 = new Board();
    saveManager = new JSONSaveManager(save);
    GameLoader loader;
    loader.loadGame(saveManager, *board1, &player1);
    QVERIFY(board1->getPiece(Position(5, 5))->equals(&piece));
    QVERIFY(board1->getPiece(Position(4, 6))->equals(&piece1));
    QVERIFY(board1->getPiece(Position(1, 9))->equals(&piece4));

    QVERIFY((*board1->getCapturedPieces(Sente).begin())->equals(&piece3));
    QVERIFY((*board1->getCapturedPieces(Gote).begin())->equals(&piece2));

    QCOMPARE(player1, player);

    delete saveManager;
    delete board;
    delete board1;

}


QTEST_APPLESS_MAIN(ShogiCoreModuleTest)

#include "tst_ShogiCoreModuleTest.moc"


