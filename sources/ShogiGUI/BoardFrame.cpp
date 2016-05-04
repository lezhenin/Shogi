#include <QtCore/QVarLengthArray>
#include <QtCore/QRect>
#include <QtCore/QDebug>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include "BoardFrame.h"



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

void BoardFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBoard(painter);
    drawPieces(painter);

    drawCapturedPieces(painter);

}

//todo зарефакторить это дерьмо!
//todo разделить на функции для каждого игрока
void BoardFrame::drawCapturedPieces(QPainter &painter) const
{
    QRect board(PADDING_LEFT() + SQUARE_WIDTH() / 2,
                PADDING_TOP() + SQUARE_HEIGHT() / 2,
                CAPTURED_PIECES_BOARD_WIDTH * SQUARE_WIDTH(),
                CAPTURED_PIECES_BOARD_HEIGHT * SQUARE_HEIGHT());

    QPainterPath path;
    path.addRoundedRect(board, 50, 25);
    painter.fillPath(path, QColor(198, 132, 00));
    painter.drawPath(path);

    int i = 1;
    for (auto &&piece : senteCapturedPieces)
    {
        QRect pieceRect(board.left() + SQUARE_WIDTH() / 2,
                        board.top()  + SQUARE_HEIGHT() * i,
                        SQUARE_WIDTH(), SQUARE_HEIGHT());

        QRect textRect(pieceRect.topRight(),
                       QSize(SQUARE_WIDTH(), SQUARE_HEIGHT()));
        painter.drawImage(pieceRect, pieceImages.at(piece.first));
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, QString::number(piece.second));
        i++;
    }

    QRect board2(width() - PADDING_RIGHT() - SQUARE_WIDTH() / 2 - CAPTURED_PIECES_BOARD_WIDTH * SQUARE_WIDTH(),
                PADDING_TOP() + SQUARE_HEIGHT() / 2,
                CAPTURED_PIECES_BOARD_WIDTH * SQUARE_WIDTH(),
                CAPTURED_PIECES_BOARD_HEIGHT * SQUARE_HEIGHT());

    QPainterPath path2;
    path2.addRoundedRect(board2, 50, 25);
    painter.fillPath(path2, QColor(198, 132, 00));
    painter.drawPath(path2);

    int i2 = 1;
    for (auto &&piece : goteCapturedPieces)
    {
        QRect pieceRect(board2.left() + SQUARE_WIDTH() / 2,
                        board2.top()  + SQUARE_HEIGHT() * i2,
                        SQUARE_WIDTH(), SQUARE_HEIGHT());

        QRect textRect(pieceRect.topRight(),
                       QSize(SQUARE_WIDTH(), SQUARE_HEIGHT()));
        painter.drawImage(pieceRect, pieceImages.at(piece.first));
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, QString::number(piece.second));
        i2++;
    }
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
    QRect boardRect(PADDING_LEFT() + SQUARE_WIDTH() * 3, PADDING_TOP() + SQUARE_HEIGHT(),
                    SQUARE_WIDTH() * BOARD_WIDTH, SQUARE_HEIGHT() * BOARD_HEIGHT);

    int x = abs(samplePiece->getPosition().getVertical()   - 9);
    int y =     samplePiece->getPosition().getHorizontal() - 1;


    QRect targetRect(boardRect.left() + SQUARE_WIDTH() * x, boardRect.top() + SQUARE_HEIGHT() * y,
                     SQUARE_WIDTH(), SQUARE_HEIGHT());

    QImage piece = pieceImages.at(samplePiece->getType());
    if (samplePiece->getPlayer() == shogi::Gote)
    {
        piece = piece.mirrored(true, true);
    }
    painter.drawImage(targetRect, piece);

    if(samplePiece == game->getPickedPiece())
    {
        painter.setPen(Qt::darkRed);
        painter.drawEllipse(targetRect);
        painter.setPen(Qt::black);
    }
}

void BoardFrame::drawBoard(QPainter &painter) const
{
    QRect boardRect(PADDING_LEFT() + SQUARE_WIDTH() * 3, PADDING_TOP(),
                    SQUARE_WIDTH() * (BOARD_WIDTH + 1), SQUARE_HEIGHT() * (BOARD_HEIGHT + 1));

    for(int i = 0; i < 9; ++i)
    {
        QRect textRect(boardRect.left() + SQUARE_WIDTH() * i, boardRect.top(),
                       SQUARE_WIDTH(), SQUARE_HEIGHT());
        painter.drawText(textRect, Qt::AlignCenter, QString::number(abs(i-BOARD_WIDTH)));

        textRect = QRect(boardRect.right() - SQUARE_WIDTH(), boardRect.top() + SQUARE_HEIGHT() * (i + 1),
                         SQUARE_WIDTH(), SQUARE_HEIGHT());
        painter.drawText(textRect, Qt::AlignCenter, QString::number(i+1));
    }
    painter.drawRect(boardRect);

    boardRect.setTop(boardRect.top() + SQUARE_HEIGHT());
    boardRect.setRight(boardRect.right() - SQUARE_WIDTH());

    painter.fillRect(boardRect, QColor(198,132,00));
    for (int i = 0; i <= BOARD_WIDTH; i++)
    {
        painter.drawLine(boardRect.left() + SQUARE_WIDTH() * i, boardRect.top(),
                         boardRect.left() + SQUARE_WIDTH() * i, boardRect.bottom());
    }
    for (int i = 0; i <= BOARD_HEIGHT; i++)
    {
        painter.drawLine(boardRect.left(),  boardRect.top() + SQUARE_HEIGHT() * i,
                         boardRect.right(), boardRect.top() + SQUARE_HEIGHT() * i);
    }
}

void BoardFrame::mousePressEvent(QMouseEvent *event)
{

    QRect boardRect(PADDING_LEFT() + SQUARE_WIDTH() * 3, PADDING_TOP() + SQUARE_WIDTH(),
                    SQUARE_WIDTH() * (BOARD_WIDTH), SQUARE_HEIGHT() * (BOARD_HEIGHT));

    if(!boardRect.contains(event->pos()))
    {
        return;
    }

    shogi::Position clickedPosition((event->y() - boardRect.top())  / SQUARE_HEIGHT() + 1,
                                abs((event->x() - boardRect.left()) / SQUARE_WIDTH() - 9));

    qDebug() << QString::number(clickedPosition.getHorizontal());
    qDebug() << QString::number(clickedPosition.getVertical());

    if(event->button() == Qt::MouseButton::LeftButton)
    if(game->getPickedPiece() == nullptr)
    {
        try
        {
            game->pickPiece(clickedPosition);
            emit sendMessage("Piece picked.");
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
            countCapturedPieces();
        }
        catch (std::exception &e)
        {
            emit sendMessage(e.what());
        }
    }
    else
    {
        game->unPickPiece();
        emit sendMessage("Piece unpicked.");
    }
    update();
}

void BoardFrame::undo() noexcept
{
    game->undo();
    update();
}

void BoardFrame::redo() noexcept
{
    game->redo();
    update();
}

//todo разделить на функции для каждого игрока
void BoardFrame::countCapturedPieces()
{
    shogi::ListOfPieces &list = game->getBoard().getCapturedPieces(shogi::Sente);
    for (auto &capturedPiece : senteCapturedPieces)
    {
        int amount = std::count_if(list.begin(), list.end(),
                                  [&capturedPiece](shogi::Piece *piece) -> bool
                                  {
                                      return piece->getType() == capturedPiece.first;
                                  });
        senteCapturedPieces[capturedPiece.first] = amount;
    }

    list = game->getBoard().getCapturedPieces(shogi::Gote);
    for (auto &capturedPiece : goteCapturedPieces)
    {
        int amount = std::count_if(list.begin(), list.end(),
                                   [&capturedPiece](shogi::Piece *piece) -> bool
                                   {
                                       return piece->getType() == capturedPiece.first;
                                   });
        goteCapturedPieces[capturedPiece.first] = amount;
    }
}











