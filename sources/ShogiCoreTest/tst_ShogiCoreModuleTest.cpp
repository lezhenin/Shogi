#include <QString>
#include <QtTest>
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
    Board board;
    board.setPiece(p1, Position(2, 2));
    board.setPiece(p2, Position(4, 5));
    BoardMemento bm(&board);
    board.removePiece(Position(2, 2));
    board.removePiece(Position(4, 5));
    QVERIFY(board.getPiece(Position(2, 2)) == nullptr);
    QVERIFY(board.getPiece(Position(4, 5)) == nullptr);
    bm.restore();
    QVERIFY(board.getPiece(Position(2, 2)) == p1);
    QVERIFY(board.getPiece(Position(4, 5)) == p2);
    delete p1;
    delete p2;

}

void ShogiCoreModuleTest::gameLogicTest()
{
    Board board;
    Piece *p1 = new Piece(Rook, Sente);
    Piece *p2 = new Piece(King, Gote);
    ShogiGameLogic g(board);
    board.setPiece(p1, Position(2,2));
    board.setPiece(p2, Position(2,4));
    QVERIFY(g.checkShah(Gote));
    QVERIFY(g.checkMove(p1,Position(2,4)));
    QVERIFY(g.checkMove(p2,Position(3,5)));
    delete p1;
    delete p2;

}


QTEST_APPLESS_MAIN(ShogiCoreModuleTest)

#include "tst_ShogiCoreModuleTest.moc"


