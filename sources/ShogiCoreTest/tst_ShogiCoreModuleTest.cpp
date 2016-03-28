#include <QString>
#include <QtTest>
#include <iostream>
#include "../ShogiCore/Model/BoardMemento.h"
#include "../ShogiCore/Shogi.h"
#include "../ShogiCore/GameLogic/ShogiGameLogic.h"

class ShogiCoreModuleTest : public QObject
{
Q_OBJECT

public:
    ShogiCoreModuleTest();

private Q_SLOTS:
    void mementoTest();
    void gameLogicTest();


private:
};

ShogiCoreModuleTest::ShogiCoreModuleTest()
{

}
void ShogiCoreModuleTest::mementoTest() {
    Piece *p1 = new Piece(Rook, Sente);
    Piece *p2 = new Piece(King, Gote);
    AbstractBoard *board = new Board();
    board->setPiece(p1, Position(2, 2));
    board->setPiece(p2, Position(4, 5));
    AbstractBoardMemento *bm = board->getMemento();
    board->removePiece(Position(2, 2));
    board->removePiece(Position(4, 5));
    QVERIFY(board->getPiece(Position(2, 2)) == nullptr);
    QVERIFY(board->getPiece(Position(4, 5)) == nullptr);
    board->setMemento(bm);
    QVERIFY(board->getPiece(Position(2, 2)) == p1);
    QVERIFY(board->getPiece(Position(4, 5)) == p2);
    delete p1;
    delete p2;
    delete board;
    delete bm;

}

void ShogiCoreModuleTest::gameLogicTest() {
    Board board;
    Piece *p1 = new Piece(Rook, Sente);
    Piece *p2 = new Piece(King, Gote);
    Piece *p3 = new Piece(Rook, Gote);
    Piece *p4 = new Piece(King, Sente);
    ShogiGameLogic g(board);
    board.setPiece(p1, Position(2, 2));
    board.setPiece(p2, Position(2, 4));
    board.setPiece(p3, Position(8, 1));
    board.setPiece(p4, Position(3, 1));
    QVERIFY(g.checkShah(Sente));
    QVERIFY(g.checkShah(Gote));
    QVERIFY(g.checkMove(p1, Position(2, 4)));
    QVERIFY(g.checkMove(p2, Position(3, 5)));
    board.removePiece(Position(2, 4));
    board.setPiece(p2, Position(9, 9));
    board.removePiece(Position(3, 1));
    board.setPiece(p4, Position(8, 8));
    board.removePiece(Position(2, 2));
    QVERIFY(!g.checkDrop(p1, Position(8, 3)));
    QVERIFY(g.checkDrop(p1, Position(6, 3)));
    board.setPiece(p1, Position(9, 2));
    QVERIFY(!g.checkMate(Gote));
    Piece *p5 = new Piece(Rook, Sente);
    board.setPiece(p5, Position(8, 3));
    QVERIFY(g.checkMate(Gote));
    Piece *p6 = new Piece(Pawn, Gote);
    QVERIFY(!g.checkDrop(p6, Position(1, 5)));
    QVERIFY(g.checkDrop(p6, Position(9, 5)));
    board.setPiece(p6,Position(1,5));
    QVERIFY(!g.checkDrop(p6, Position(7,5)));
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6;
}

QTEST_APPLESS_MAIN(ShogiCoreModuleTest)

#include "tst_ShogiCoreModuleTest.moc"


