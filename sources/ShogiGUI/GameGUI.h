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
    explicit GameGUI(QWidget *parent);

    void load(QString &saveDate);

    virtual ~GameGUI() { }

private:

    const QSize SCREEN_SIZE{1120, 640};
    const QSize GRAPHIC_ZONE_SIZE{960, 600};
    const QSize BUTTON_SIZE{145, 50};

    static constexpr int PADDING = 5;

    QString QPushButtonStyle =
            "QPushButton "
                    "{"
                    " border: 1px solid #000000;"
                    " background: #8f5732; "
                    " background: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,  stop: 0 #f59356, stop: 1 #8f5732);"
                    " padding: 7.5px 15px;"
                    " border-radius: 8px;"
                    " color: #ffffff;"
                    " font-size: 22px;"
                    "}"
                    "QPushButton:pressed "
                    "{"
                    " border-color #f59356;"
                    " background: #f59356;"
                    "}"
                    "QPushButton:flat "
                    "{"
                    " border: none;"
                    "}";

    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *menuButton;
    QPushButton *exitButton;

    QLabel *status;

    BoardFrame *board;

    void sendQuestionMessage(const std::shared_ptr<shogi::GameSituation> &situation);
    void sendInformativeMessage(const std::shared_ptr<shogi::GameSituation> &situation);

private slots:

    void showMessage(QString msg);

    void save();
    void load();
    void undo();
    void redo();
    void exit();
    void menu();

    void handleGameSituation(const std::shared_ptr<shogi::GameSituation> &situation);

};


#endif //SHOGI_GAMEGUI_H
