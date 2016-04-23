#ifndef SHOGI_MAINMENU_H
#define SHOGI_MAINMENU_H

#include <QtWidgets/QWidget>

class MainMenuG: public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuG(QWidget *parent);

    static const int HEIGHT = 600;
    static const int WIDTH = 800;

private slots:

    void exit();

};


#endif //SHOGI_MAINMENU_H
