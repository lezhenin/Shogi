#include <QtGui/QPainter>
#include "BoardFrame.h"
#include "../ShogiCore/API/Shogi.h"

BoardFrame::BoardFrame(QWidget *parent, int pixelsPerSquare) : QFrame(parent), PIXELS_PER_SQUARE(pixelsPerSquare)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    game = new shogi::Shogi();
    game->load();
}

BoardFrame::~BoardFrame()
{
    delete game;
}

QSize BoardFrame::sizeHint() const
{
    return QSize(BOARD_WIDTH  * PIXELS_PER_SQUARE + frameWidth() * 2,
                 BOARD_HEIGHT * PIXELS_PER_SQUARE + frameWidth() * 2);
}

void BoardFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    drawBoard(painter);
    drawPieces(painter);

}

void BoardFrame::drawPieces(QPainter &painter) const {
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; j++)
        {
            shogi::Piece *samplePiece = game->getBoard().getPiece(this->Position(i + 1, j + 1));
            if(samplePiece != nullptr)
            {
                painter.drawEllipse(width() / BOARD_WIDTH * j, height() / BOARD_HEIGHT * i, width() / BOARD_WIDTH, height() /
                                                                                                                   BOARD_HEIGHT);
            }
        }
    }
}

void BoardFrame::drawBoard(QPainter &painter) const {
    for (int i = 1; i < BOARD_WIDTH; i++)
    {
        painter.drawLine((width() / BOARD_WIDTH) * i, 0, (width() / BOARD_WIDTH) * i, height());
    }
    for (int i = 1; i < BOARD_HEIGHT; i++)
    {
        painter.drawLine(0, (height() / BOARD_HEIGHT) * i , width(), (height() / BOARD_HEIGHT) * i );
    }
    painter.drawRect(0, 0, width() - 1, height() - 1);
}







