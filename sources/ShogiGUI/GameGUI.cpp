#include <QtWidgets/QAbstractButton>
#include "GameGUI.h"


GameGUI::GameGUI(QWidget *parent): QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    this->setFixedSize(SCREEN_SIZE);

    board = new BoardFrame(this);

    undoButton = new QPushButton(tr("Undo"), this);
    undoButton->setFocusPolicy(Qt::NoFocus);
    connect(undoButton, SIGNAL(clicked()), board, SLOT(undo()));

    redoButton = new QPushButton(tr("Redo"), this);
    redoButton->setFocusPolicy(Qt::NoFocus);
    connect(redoButton, SIGNAL(clicked()), board, SLOT(redo()));

    saveButton = new QPushButton(tr("Save"), this);
    saveButton->setFocusPolicy(Qt::NoFocus);

    loadButton = new QPushButton(tr("Load"), this);
    loadButton->setFocusPolicy(Qt::NoFocus);

    exitButton = new QPushButton(tr("Exit"), this);
    exitButton->setFocusPolicy(Qt::NoFocus);

    menuButton = new QPushButton(tr("Menu"), this);
    menuButton->setFocusPolicy(Qt::NoFocus);

    status = new QLabel(this);
    status->setWordWrap(true);
    QFont labelFont = status->font();
    labelFont.setPointSize(14);
    status->setFont(labelFont);
    connect(board, SIGNAL(sendMessage(QString)), status, SLOT(setText(QString)));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 1, 12, 6);
    layout->addWidget(undoButton, 0, 7);
    layout->addWidget(redoButton, 1, 7);
    layout->addWidget(saveButton, 2, 7);
    layout->addWidget(loadButton, 3, 7);
    layout->addWidget(menuButton, 4, 7);
    layout->addWidget(exitButton, 5, 7);
    layout->addWidget(status, 6, 7);
    setLayout(layout);

    status->setFixedWidth(status->width());
    setWindowTitle(tr("Shogi"));
}



