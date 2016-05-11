#ifndef SHOGI_GAMEGUI_H
#define SHOGI_GAMEGUI_H

#include "../ShogiCore/API/Shogi.h"
#include <QtGuiDepends>
#include <QtWidgets>
#include "BoardFrame.h"

class GameGUI : public QWidget
{
    Q_OBJECT



public:
    explicit GameGUI(QWidget *parent, bool needLoad = false);

    virtual ~GameGUI() { }

private:

    const QSize SCREEN_SIZE{1020, 600};

    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *menuButton;
    QPushButton *exitButton;

    QLabel *status;

    BoardFrame *board;

    void sendQuestionMessage(const std::shared_ptr<shogi::GameSituation> &situation);
    void sendInformativeMessage(const std::shared_ptr<shogi::GameSituation> &situation) const;

private slots:

    void save();
    void load();
    void undo();
    void redo();

    void handleGameSituation(const std::shared_ptr<shogi::GameSituation> &situation);
};


#endif //SHOGI_GAMEGUI_H
