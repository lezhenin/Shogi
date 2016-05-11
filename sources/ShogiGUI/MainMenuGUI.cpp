#include "MainMenuGUI.h"
#include "GameGUI.h"

void MainMenuG::exit()
{
    this->close();
}

MainMenuG::MainMenuG(QWidget *parent) : QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    this->setFixedSize(SCREEN_SIZE);

    QPixmap background(":/menu_background2.png");
    QPalette qPalette;
    qPalette.setBrush(this->backgroundRole(),QBrush(background));
    this->setPalette(qPalette);

    exitButton = new QPushButton(this);

    exitButton->setStyleSheet(QPushButtonStyle);
    exitButton->setText(tr("Exit"));
    exitButton->resize(BUTTON_SIZE);
    exitButton->move(SCREEN_SIZE.width()  - BUTTON_SIZE.width()  - 30,
                     SCREEN_SIZE.height() - BUTTON_SIZE.height() - 20);

    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));

    loadButton = new QPushButton(this);
    loadButton->setStyleSheet(QPushButtonStyle);
    loadButton->setText(tr("Load"));
    loadButton->resize(BUTTON_SIZE);
    loadButton->move(SCREEN_SIZE.width()  - BUTTON_SIZE.width()  - 30,
                      SCREEN_SIZE.height() - BUTTON_SIZE.height() * 2 - 20 - 5);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    startButton = new QPushButton(this);
    startButton->setStyleSheet(QPushButtonStyle);
    startButton->setText(tr("Start"));
    startButton->resize(BUTTON_SIZE);
    startButton->move(SCREEN_SIZE.width()  - BUTTON_SIZE.width()  - 30,
                      SCREEN_SIZE.height() - BUTTON_SIZE.height() * 3 - 20 - 5 * 2);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
}

void MainMenuG::loadGame()
{
    GameGUI *game = new GameGUI(0, true);
    game->show();
    exit();
}

void MainMenuG::startGame()
{
    GameGUI *game = new GameGUI(0, false);
    game->show();
    exit();
}






