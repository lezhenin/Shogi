#include <QtWidgets/qgridlayout.h>
#include "GameGUI.h"
#include "BoardFrame.h"

GameGUI::GameGUI(QWidget *parent): QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    this->setFixedSize(SCREEN_SIZE);

    undoButton = new QPushButton("Undo", this);
    undoButton->setFocusPolicy(Qt::NoFocus);

    redoButton = new QPushButton("Redo", this);
    redoButton->setFocusPolicy(Qt::NoFocus);

    saveButton = new QPushButton("Save", this);
    saveButton->setFocusPolicy(Qt::NoFocus);

    loadButton = new QPushButton("Load", this);
    loadButton->setFocusPolicy(Qt::NoFocus);

    exitButton = new QPushButton("Exit", this);
    exitButton->setFocusPolicy(Qt::NoFocus);

    menuButton = new QPushButton("Menu", this);
    menuButton->setFocusPolicy(Qt::NoFocus);

    board = new BoardFrame(this, 50);



    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 1, 12, 6);
    layout->addWidget(undoButton, 0, 7);
    layout->addWidget(redoButton, 1, 7);
    layout->addWidget(saveButton, 2, 7);
    layout->addWidget(loadButton, 3, 7);
    layout->addWidget(menuButton, 4, 7);
    layout->addWidget(exitButton, 5, 7);
    setLayout(layout);

    setWindowTitle("Shogi");
}



