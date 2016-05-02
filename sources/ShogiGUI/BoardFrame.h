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
    virtual ~BoardFrame();
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:

    void undo();
    void redo();

protected:

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void sendMessage(QString message);

private:

    const int BOARD_HEIGHT = shogi::AbstractBoard::BOARD_HEIGHT;
    const int BOARD_WIDTH = shogi::AbstractBoard::BOARD_WIDTH;
    const int PIXELS_PER_SQUARE_Y() const { return height() / (BOARD_HEIGHT + 1); }
    const int PIXELS_PER_SQUARE_X() const { return width()  / (BOARD_WIDTH + 7); }
    const int PADDING_LEFT() const   { return (width() - PIXELS_PER_SQUARE_X() * (BOARD_WIDTH + 7)) / 2; }
    const int PADDING_RIGHT() const  { return  width() - PIXELS_PER_SQUARE_X() * (BOARD_WIDTH + 7) - PADDING_LEFT(); }
    const int PADDING_TOP() const    { return (height() - PIXELS_PER_SQUARE_Y() * (BOARD_HEIGHT + 1)) / 2; }
    const int PADDING_BOTTOM() const { return  height() - PIXELS_PER_SQUARE_Y() * (BOARD_HEIGHT + 1)/2 - PADDING_TOP(); }

    void drawBoard(QPainter &painter) const;
    void drawPiece(QPainter &painter, const shogi::Piece *samplePiece) const;
    void drawPieces(QPainter &painter) const;

    shogi::GameAPI *game;

private slots:


};


#endif //SHOGI_BOARDFRAME_H
