#ifndef SHOGI_BOARDFRAME_H
#define SHOGI_BOARDFRAME_H

#include <QtWidgets/QFrame>
#include "../ShogiCore/API/GameAPI.h"

class BoardFrame : public QFrame
{
    Q_OBJECT
public:

    explicit BoardFrame(QWidget *parent = 0, int pixelsPerSquare = 15);
    virtual ~BoardFrame();
    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:

    const int BOARD_HEIGHT = shogi::AbstractBoard::BOARD_HEIGHT;
    const int BOARD_WIDTH = shogi::AbstractBoard::BOARD_WIDTH;
    const int PIXELS_PER_SQUARE;

    shogi::GameAPI *game;

private slots:

    void drawBoard(QPainter &painter) const;

    void drawPieces(QPainter &painter) const;
};


#endif //SHOGI_BOARDFRAME_H
