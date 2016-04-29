#ifndef SHOGI_GAMEGUI_H
#define SHOGI_GAMEGUI_H

#include "../ShogiCore/API/Shogi.h"
#include <QtWidgets/QWidget>

class GameGUI : public QWidget
{
    Q_OBJECT

public:
    explicit GameGUI(QWidget *parent);


    virtual ~GameGUI();

private:

    const QSize SCREEN_SIZE{800, 600};
    shogi::GameAPI *game;

private slots:
};


#endif //SHOGI_GAMEGUI_H
