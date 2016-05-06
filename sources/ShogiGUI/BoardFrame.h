#ifndef SHOGI_BOARDFRAME_H
#define SHOGI_BOARDFRAME_H

#include <QtGuiDepends>
#include <QtWidgets>
#include "../ShogiCore/API/Shogi.h"

class BoardFrame : public QFrame
{
    Q_OBJECT
public:

    explicit BoardFrame(QWidget *parent = 0);
    virtual ~BoardFrame() noexcept;

public slots:

    void undo() noexcept;
    void redo() noexcept;

protected:

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:

    void sendMessage(QString message);

private:

    const int BOARD_HEIGHT = shogi::AbstractBoard::BOARD_HEIGHT;
    const int BOARD_WIDTH  = shogi::AbstractBoard::BOARD_WIDTH;
    const int CAPTURE_BOARD_HEIGHT = 9;
    const int CAPTURE_BOARD_WIDTH = 2;
    const int SQUARE_HEIGHT()  const noexcept { return  height() / (BOARD_HEIGHT + 1); }
    const int SQUARE_WIDTH()   const noexcept { return  width()  / (BOARD_WIDTH + 7); }
    const int PADDING_LEFT()   const noexcept { return (width()  - SQUARE_WIDTH()  * (BOARD_WIDTH  + 7)) / 2; }
    const int PADDING_RIGHT()  const noexcept { return  width()  - SQUARE_WIDTH()  * (BOARD_WIDTH  + 7) - PADDING_LEFT(); }
    const int PADDING_TOP()    const noexcept { return (height() - SQUARE_HEIGHT() * (BOARD_HEIGHT + 1)) / 2; }
    const int PADDING_BOTTOM() const noexcept { return  height() - SQUARE_HEIGHT() * (BOARD_HEIGHT + 1) - PADDING_TOP(); }

    const QRect BOARD_RECT()     const noexcept { return QRect(PADDING_LEFT() + SQUARE_WIDTH() * 3,
                                                         PADDING_TOP(),
                                                         SQUARE_WIDTH()  * (BOARD_WIDTH + 1),
                                                         SQUARE_HEIGHT() * (BOARD_HEIGHT + 1));}

    const QRect GAME_ZONE_RECT() const noexcept { return QRect(PADDING_LEFT() + SQUARE_WIDTH() * 3,
                                                         PADDING_TOP()  + SQUARE_WIDTH(),
                                                         SQUARE_WIDTH()  * (BOARD_WIDTH),
                                                         SQUARE_HEIGHT() * (BOARD_HEIGHT));}

    const QRect GOTE_CAPTURE_BOARD()  const noexcept { return QRect(PADDING_LEFT() + SQUARE_WIDTH()  / 2,
                                                                    PADDING_TOP()  + SQUARE_HEIGHT() / 2,
                                                                    CAPTURE_BOARD_WIDTH  * SQUARE_WIDTH(),
                                                                    CAPTURE_BOARD_HEIGHT * SQUARE_HEIGHT());}

    const QRect SENTE_CAPTURE_BOARD() const noexcept { return QRect(width() - PADDING_RIGHT() - SQUARE_WIDTH() / 2
                                                           - CAPTURE_BOARD_WIDTH * SQUARE_WIDTH(),
                                                           PADDING_TOP() + SQUARE_HEIGHT() / 2,
                                                           CAPTURE_BOARD_WIDTH  * SQUARE_WIDTH(),
                                                           CAPTURE_BOARD_HEIGHT * SQUARE_HEIGHT());}

    void drawBoard(QPainter &painter) const noexcept ;
    void drawPiece(QPainter &painter, const shogi::Piece *samplePiece) const noexcept ;
    void drawPieces(QPainter &painter) const noexcept ;
    void drawCapturedPieces(QPainter &painter, const shogi::Player &player) const noexcept ;

    void onGameZoneClicked(const QMouseEvent *event) noexcept ;

    void countCapturedPieces(const shogi::Player &player) noexcept ;

    const std::map<shogi::PieceType, QImage> pieceImages =
            {
                    {shogi::GoldGeneral,   QImage(":/pieces/gold_general.png")},
                    {shogi::Rook,          QImage(":/pieces/rook.png")},
                    {shogi::Bishop,        QImage(":/pieces/bishop.png")},
                    {shogi::SilverGeneral, QImage(":/pieces/silver_general.png")},
                    {shogi::Knight,        QImage(":/pieces/knight.png")},
                    {shogi::Lance,         QImage(":/pieces/lance.png")},
                    {shogi::King,          QImage(":/pieces/king.png")},
                    {shogi::Pawn,          QImage(":/pieces/pawn.png")},

                    {shogi::PromotedRook,          QImage(":/pieces/pawn.png")},
                    {shogi::PromotedBishop,        QImage(":/pieces/pawn.png")},
                    {shogi::PromotedKnight,        QImage(":/pieces/pawn.png")},
                    {shogi::PromotedSilverGeneral, QImage(":/pieces/pawn.png")},
                    {shogi::PromotedPawn,          QImage(":/pieces/pawn.png")},
                    {shogi::PromotedLance,         QImage(":/pieces/pawn.png")}
            };

    std::map<shogi::PieceType, int> senteCapturedPieces =
            {
                    {shogi::GoldGeneral,   0},
                    {shogi::Rook,          0},
                    {shogi::Bishop,        0},
                    {shogi::SilverGeneral, 0},
                    {shogi::Knight,        0},
                    {shogi::Lance,         0},
                    {shogi::Pawn,          0}
            };
    std::map<shogi::PieceType, int> goteCapturedPieces =
            {
                    {shogi::GoldGeneral,   0},
                    {shogi::Rook,          0},
                    {shogi::Bishop,        0},
                    {shogi::SilverGeneral, 0},
                    {shogi::Knight,        0},
                    {shogi::Lance,         0},
                    {shogi::Pawn,          0}
            };

    shogi::GameAPI *game;
};


#endif //SHOGI_BOARDFRAME_H
