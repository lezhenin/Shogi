#include <QtCore/QVarLengthArray>
#include <QtCore/QRect>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include "GameGraphicFrame.h"
#include "../ShogiCore/SaveAndLoad/JSON/JSONSaveManager.h"



GameGraphicFrame::GameGraphicFrame(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel );
    setFocusPolicy(Qt::StrongFocus);

    QPixmap background(":/board_background.jpg");
    QPalette qPalette;
    qPalette.setBrush(this->backgroundRole(),QBrush(background));
    this->setAutoFillBackground(true);
    this->setPalette(qPalette);

    game = new shogi::Shogi();
    game->load();
}

GameGraphicFrame::~GameGraphicFrame()
{
    delete game;
}

void GameGraphicFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBoard(painter);
    drawPieces(painter);

    drawCapturedPieces(painter, shogi::Gote);
    drawCapturedPieces(painter, shogi::Sente);

}

void GameGraphicFrame::drawCapturedPieces(QPainter &painter, const shogi::Player &player) const noexcept
{
    QRect CAPTURE_BOARD;
    std::map<shogi::PieceType, int> capturedPieces;
    if(player == shogi::Sente)
    {
        capturedPieces = senteCapturedPieces;
        CAPTURE_BOARD = QRect(SENTE_CAPTURE_BOARD().topLeft(),
                              SENTE_CAPTURE_BOARD().bottomRight());
    }
    else
    {
        capturedPieces = goteCapturedPieces;
        CAPTURE_BOARD = QRect(GOTE_CAPTURE_BOARD().topLeft(),
                              GOTE_CAPTURE_BOARD().bottomRight());
    }

    painter.drawImage(CAPTURE_BOARD,QImage(":side_board_texture.jpg"));
    painter.drawRect(CAPTURE_BOARD);

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(13);
    painter.setFont(font);
    QRect text(CAPTURE_BOARD.topLeft(),QSize(CAPTURE_BOARD.width(),SQUARE_HEIGHT()));

    painter.drawText(text, ((player == shogi::Sente) ? "Sente" : "Gote"),
                     QTextOption(Qt::AlignCenter | Qt::AlignHCenter));

    int i = 1;
    for (auto &piece : capturedPieces)
    {
        QRect pieceRect(CAPTURE_BOARD.left() + SQUARE_WIDTH() / 2,
                        CAPTURE_BOARD.top()  + SQUARE_HEIGHT() * i,
                        SQUARE_WIDTH(), SQUARE_HEIGHT());
        painter.drawImage(pieceRect, pieceImages.at(piece.first));

        if(pieceForDrop != nullptr && piece.first == *pieceForDrop &&
           game->getCurrentPlayer() == player)
        {
            painter.drawEllipse(pieceRect);
        }

        QRect textRect(pieceRect.topRight(),
                       QSize(SQUARE_WIDTH(), SQUARE_HEIGHT()));
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom,
                         QString::number(piece.second));
        i++;
    }

}

void GameGraphicFrame::drawPieces(QPainter &painter) const noexcept
{
    for (shogi::Piece* piece : game->getBoard().getPiecesOnBoard())
    {
        drawPiece(painter, piece);
    }
}

void GameGraphicFrame::drawPiece(QPainter &painter, const shogi::Piece *samplePiece) const noexcept
{
    int x = abs(samplePiece->getPosition().getVertical()   - 9);
    int y =     samplePiece->getPosition().getHorizontal() - 1;


    QRect targetRect(GAME_ZONE_RECT().left() + SQUARE_WIDTH() * x,
                     GAME_ZONE_RECT().top() + SQUARE_HEIGHT() * y,
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

void GameGraphicFrame::drawBoard(QPainter &painter) const noexcept
{
    painter.drawImage(BOARD_RECT(),QImage(":/board_texture.jpg"));
    painter.drawRect(BOARD_RECT());

    for (int i = 0; i <= BOARD_WIDTH; i++)
    {
        painter.drawLine(GAME_ZONE_RECT().left() + SQUARE_WIDTH() * i, GAME_ZONE_RECT().top(),
                         GAME_ZONE_RECT().left() + SQUARE_WIDTH() * i, GAME_ZONE_RECT().bottom());
    }
    for (int i = 0; i <= BOARD_HEIGHT; i++)
    {
        painter.drawLine(GAME_ZONE_RECT().left(),  GAME_ZONE_RECT().top() + SQUARE_HEIGHT() * i,
                         GAME_ZONE_RECT().right(), GAME_ZONE_RECT().top() + SQUARE_HEIGHT() * i);
    }
}

void GameGraphicFrame::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        onRightButtonClicked();
        update();
        return;
    }

    if(GAME_ZONE_RECT().contains(event->pos()))
    {
        onGameZoneClicked(event);
    }
    if(SENTE_CAPTURE_BOARD().contains(event->pos()))
    {
        onCaptureBoardClicked(event, shogi::Sente);
    }
    if(GOTE_CAPTURE_BOARD().contains(event->pos()))
    {
        onCaptureBoardClicked(event, shogi::Gote);
    }
    update();

}

void GameGraphicFrame::onCaptureBoardClicked(const QMouseEvent *event, const shogi::Player &player) noexcept
{

    auto &capturedPieces  = senteCapturedPieces;
    QRect captureBoard;

    if(player == shogi::Sente)
    {
        captureBoard = QRect(SENTE_CAPTURE_BOARD().topLeft(),
                              SENTE_CAPTURE_BOARD().bottomRight());
    }
    else
    {
        capturedPieces = goteCapturedPieces;
        captureBoard = QRect(GOTE_CAPTURE_BOARD().topLeft(),
                              GOTE_CAPTURE_BOARD().bottomRight());
    }

    QRect activeZone(captureBoard.left() + SQUARE_WIDTH() / 2,
                     captureBoard.top() + SQUARE_HEIGHT() ,
                     SQUARE_WIDTH(), SQUARE_HEIGHT() * capturedPieces.size());

    if(!activeZone.contains(event->pos()))
    {
        return;
    }

    if(game->getCurrentPlayer() != player)
    {
        emit sendMessage(tr("This piece don't belong you"));
        return;
    }


    int number = (event->y() - activeZone.top()) / SQUARE_HEIGHT();
    auto piece = capturedPieces.begin();
    for(int i = 0; i < number; i++)
    {
        piece++;
    }
    pieceForDrop = &piece->first;
}

void GameGraphicFrame::onGameZoneClicked(const QMouseEvent *event) noexcept
{
    shogi::Position clickedPosition((event->y() - GAME_ZONE_RECT().top()) / SQUARE_HEIGHT() + 1,
                                abs((event->x() - GAME_ZONE_RECT().left()) / SQUARE_WIDTH() - 9));

    if(pieceForDrop != nullptr)
    {
        try
        {
            game->dropPiece(*pieceForDrop, clickedPosition);
            pieceForDrop = nullptr;
        }
        catch (shogi::BadDropException &e)
        {
            emit sendMessage(tr("You can't drop this piece here."));
        }
        return;
    }

    if (game->getPickedPiece() == nullptr)
    {
        try
        {
            game->pickPiece(clickedPosition);
            emit sendMessage(tr("Piece picked."));
        }
        catch (shogi::BadPickException &e)
        {
            emit sendMessage(tr("You can't pick this piece."));
        }

    }
    else
    {
        try
        {
            game->movePiece(clickedPosition);
        }
        catch (shogi::BadMoveException &e)
        {
            emit sendMessage(tr("You can't move this piece here."));
        }
    }
}

void GameGraphicFrame::onRightButtonClicked() noexcept
{
    if(pieceForDrop != nullptr)
        {
            pieceForDrop = nullptr;
        }
    if(game->getPickedPiece() != nullptr)
        {
            game->unPickPiece();
            emit sendMessage(tr("Piece unpicked."));
        }
}

void GameGraphicFrame::undo() noexcept
{
    game->undo();
    update();
}

void GameGraphicFrame::redo() noexcept
{
    game->redo();
    update();
}


void GameGraphicFrame::countCapturedPieces(const shogi::Player &player) noexcept
{
    const shogi::ListOfPieces &list = game->getBoard().getCapturedPieces(player);
    std::map<shogi::PieceType, int> &capturedPieces = (player == shogi::Sente) ? senteCapturedPieces : goteCapturedPieces;

    for (auto &capturedPiece : capturedPieces)
    {
        int amount = std::count_if(list.begin(), list.end(),
                                  [&capturedPiece](shogi::Piece *piece) -> bool
                                  {
                                      return piece->getType() == capturedPiece.first;
                                  });
       capturedPieces[capturedPiece.first] = amount;
    }
}

void GameGraphicFrame::checkGameSituations(shogi::ListOfGameSituations &list) noexcept
{
    while(!list.empty())
    {
        sendGameSituation(list.front());
        list.pop();
    }
}

void GameGraphicFrame::update()
{
    countCapturedPieces(shogi::Sente);
    countCapturedPieces(shogi::Gote);
    checkGameSituations(game->getGameSituation());
    QWidget::update();
}

std::string GameGraphicFrame::save()
{
    shogi::JSONSaveManager manager;
    game->save(&manager);
    return manager.getJSONString();
}

void GameGraphicFrame::load(const std::string &save)
{
    shogi::JSONSaveManager manager(save);
    game->load(&manager);
}

void GameGraphicFrame::load()
{
    game->load();
}










