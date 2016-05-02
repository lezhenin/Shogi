#include <QtCore/QVarLengthArray>
#include <QtCore/QRect>
#include <QtCore/QDebug>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include "BoardFrame.h"
#include "../ShogiCore/API/Shogi.h"

BoardFrame::BoardFrame(QWidget *parent) : QFrame(parent)
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
    return QSize(BOARD_WIDTH  * /*PIXELS_PER_SQUARE_X()*/ + frameWidth() * 2,
                 BOARD_HEIGHT * /*PIXELS_PER_SQUARE_Y()*/ + frameWidth() * 2);
}

void BoardFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    drawBoard(painter);
    drawPieces(painter);

}

void BoardFrame::drawPieces(QPainter &painter) const
{
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; j++)
        {
            shogi::Piece *samplePiece = game->getBoard().getPiece(shogi::Position(i + 1, j + 1));
            if(samplePiece != nullptr)
            {
                drawPiece(painter, samplePiece);
            }
        }
    }
}

void BoardFrame::drawPiece(QPainter &painter, const shogi::Piece *samplePiece) const
{
    QRect boardRect(PADDING_LEFT() + PIXELS_PER_SQUARE_X() * 3, PADDING_TOP() + PIXELS_PER_SQUARE_Y(),
                    PIXELS_PER_SQUARE_X() * BOARD_WIDTH, PIXELS_PER_SQUARE_Y() * BOARD_HEIGHT);

    int x = abs(samplePiece->getPosition().getVertical()   - 9);
    int y =     samplePiece->getPosition().getHorizontal() - 1;


    QRect targetRect(boardRect.left() + PIXELS_PER_SQUARE_X() * x, boardRect.top() + PIXELS_PER_SQUARE_Y() * y,
                     PIXELS_PER_SQUARE_X(), PIXELS_PER_SQUARE_Y());

    QImage piece(":/pieces/pawn.png");
    if (samplePiece->getPlayer() == shogi::Gote)
    {
        piece = piece.mirrored(true, true);
    }
    painter.drawImage(targetRect, piece);
}

void BoardFrame::drawBoard(QPainter &painter) const
{
    QRect boardRect(PADDING_LEFT() + PIXELS_PER_SQUARE_X() * 3, PADDING_TOP(),
                    PIXELS_PER_SQUARE_X() * (BOARD_WIDTH + 1), PIXELS_PER_SQUARE_Y() * (BOARD_HEIGHT + 1));

    for(int i = 0; i < 9; ++i)
    {
        QRect textRect(boardRect.left() + PIXELS_PER_SQUARE_X() * i, boardRect.top(),
                       PIXELS_PER_SQUARE_X(), PIXELS_PER_SQUARE_Y());
        painter.drawText(textRect, Qt::AlignCenter, QString::number(abs(i-BOARD_WIDTH)));

        textRect = QRect(boardRect.right() - PIXELS_PER_SQUARE_X(), boardRect.top() + PIXELS_PER_SQUARE_Y() * (i + 1),
                         PIXELS_PER_SQUARE_X(), PIXELS_PER_SQUARE_Y());
        painter.drawText(textRect, Qt::AlignCenter, QString::number(i+1));
    }

    boardRect.setTop(boardRect.top() + PIXELS_PER_SQUARE_Y());
    boardRect.setRight(boardRect.right() - PIXELS_PER_SQUARE_X());
    for (int i = 0; i <= BOARD_WIDTH; i++)
    {
        painter.drawLine(boardRect.left() + PIXELS_PER_SQUARE_X() * i, boardRect.top(),
                         boardRect.left() + PIXELS_PER_SQUARE_X() * i, boardRect.bottom());
    }
    for (int i = 0; i <= BOARD_HEIGHT; i++)
    {
        painter.drawLine(boardRect.left(),  boardRect.top() + PIXELS_PER_SQUARE_Y() * i,
                         boardRect.right(), boardRect.top() + PIXELS_PER_SQUARE_Y() * i);
    }
}

void BoardFrame::mousePressEvent(QMouseEvent *event)
{

    QRect boardRect(PADDING_LEFT() + PIXELS_PER_SQUARE_X() * 3, PADDING_TOP() + PIXELS_PER_SQUARE_X(),
                    PIXELS_PER_SQUARE_X() * (BOARD_WIDTH), PIXELS_PER_SQUARE_Y() * (BOARD_HEIGHT));

    if(!boardRect.contains(event->pos()))
    {
        return;
    }

    shogi::Position clickedPosition((event->y() - boardRect.top())  / PIXELS_PER_SQUARE_Y() + 1,
                                abs((event->x() - boardRect.left()) / PIXELS_PER_SQUARE_X() - 9));

    qDebug() << QString::number(clickedPosition.getHorizontal());
    qDebug() << QString::number(clickedPosition.getVertical());

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









