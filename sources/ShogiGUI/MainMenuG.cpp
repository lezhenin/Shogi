#include <QtWidgets/QToolButton>
#include <QtWidgets/QGridLayout>
#include "MainMenuG.h"

void MainMenuG::exit()
{
    this->close();
}

MainMenuG::MainMenuG(QWidget *parent) : QWidget(parent)
{
    QToolButton *exitButton = new QToolButton;
    exitButton->setText("Exit");
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(exitButton);
    this->setLayout(gridLayout);
}



