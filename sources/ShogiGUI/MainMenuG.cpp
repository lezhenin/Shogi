#include <QtWidgets/QToolButton>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTextStream>
#include <QtWidgets/QPushButton>
#include <QtGui/QTextFormat>
#include "MainMenuG.h"

void MainMenuG::exit()
{
    this->close();
}

MainMenuG::MainMenuG(QWidget *parent) : QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    this->setFixedHeight(HEIGHT);
    this->setFixedWidth(WIDTH);

    QPixmap background(":/menu_background.png");
    QPalette qPalette;
    qPalette.setBrush(this->backgroundRole(),QBrush(background));
    this->setPalette(qPalette);

    QPushButton *exitButton = new QPushButton(this);
    exitButton->setText("Exit");
    exitButton->resize(150,50);
    exitButton->move(WIDTH-155, HEIGHT-55);
   // exitButton->setStyleSheet("QPushButton {border-radius: 10px;}");
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));

}



