#include "GameGUI.h"

GameGUI::GameGUI(QWidget *parent): QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    this->setFixedSize(SCREEN_SIZE);
    game = new shogi::Shogi();
}

GameGUI::~GameGUI()
{
    delete game;
}

