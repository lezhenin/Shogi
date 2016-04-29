#ifndef SHOGI_GAMEGUI_H
#define SHOGI_GAMEGUI_H

#include "../ShogiCore/API/Shogi.h"
#include "BoardFrame.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

class GameGUI : public QWidget
{
    Q_OBJECT

public:
    explicit GameGUI(QWidget *parent);

    virtual ~GameGUI() { }

private:

    const QSize SCREEN_SIZE{800, 600};

    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *menuButton;
    QPushButton *exitButton;

    BoardFrame *board;

private slots:
};


#endif //SHOGI_GAMEGUI_H
