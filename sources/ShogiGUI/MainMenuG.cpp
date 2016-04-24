#include <QtWidgets/QToolButton>
#include <QtWidgets/QGridLayout>
#include <QtCore/QTextStream>
#include <QtWidgets/QPushButton>
#include <QtGui/QTextFormat>
#include <QtGui/QBitmap>
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
//    QPixmap pix(":/s_icon.png");
//    QIcon icon(pix);
//    exitButton->setIcon(icon);
//    exitButton->setIconSize(pix.size());
//    exitButton->setIcon(icon);
    exitButton->setStyleSheet("QPushButton "
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
                                         "}");
    exitButton->setText("Exit");
    exitButton->resize(150,50);
    exitButton->move(WIDTH-155, HEIGHT-55);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));

}



