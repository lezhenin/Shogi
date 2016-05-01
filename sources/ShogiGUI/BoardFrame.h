#ifndef SHOGI_BOARDFRAME_H
#define SHOGI_BOARDFRAME_H

#include <QtGuiDepends>
#include <QtWidgets>
#include "../ShogiCore/API/Shogi.h"

class BoardFrame : public QFrame
{
    Q_OBJECT
public:

    explicit BoardFrame(QWidget *parent = 0, int pixelsPerSquare = 15);
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
    const int PIXELS_PER_SQUARE;

    void drawBoard(QPainter &painter) const;
    void drawPieces(QPainter &painter) const;

    shogi::GameAPI *game;

private slots:

};


#endif //SHOGI_BOARDFRAME_H
