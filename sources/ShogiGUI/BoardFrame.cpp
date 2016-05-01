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
            shogi::Piece *samplePiece = game->getBoard().getPiece(shogi::Position(i + 1, j + 1));
            if(samplePiece != nullptr)
            {
                if(samplePiece->getPlayer() == shogi::Gote)
                {
                    painter.setPen(Qt::red);
                }
                else
                {
                    painter.setPen(Qt::black);
                }
                painter.drawEllipse(width() / BOARD_WIDTH * j, height() / BOARD_HEIGHT * i,
                                    width() / BOARD_WIDTH, height() / BOARD_HEIGHT);
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

void BoardFrame::mousePressEvent(QMouseEvent *event)
{
    shogi::Position clickedPosition(event->y() / (height() / BOARD_HEIGHT) + 1, event->x() / (width() / BOARD_WIDTH) + 1);
    if(event->button() == Qt::MouseButton::LeftButton)
    if(game->getPickedPiece() == nullptr)
    {
        try
        {
            game->pickPiece(clickedPosition);
        }
        catch (std::exception &e)
        {
            emit sendMessage(e.what());
        }
    }
    else
    {
        try
        {
            game->movePiece(clickedPosition);
        }
        catch (std::exception &e)
        {
            emit sendMessage(e.what());
        }
    }
    else
    {
        game->unPickPiece();
    }
    update();
}

void BoardFrame::undo()
{
    game->undo();
    update();
}

void BoardFrame::redo()
{
    game->redo();
    update();
}









