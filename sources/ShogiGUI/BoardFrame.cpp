#include "BoardFrame.h"
#include "../ShogiCore/API/Shogi.h"

BoardFrame::BoardFrame(QWidget *parent, int pixelsPerSquare) : QFrame(parent), PIXELS_PER_SQUARE(pixelsPerSquare)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    game = new shogi::Shogi();
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
}







