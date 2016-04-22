#ifndef SHOGI_MAINMENU_H
#define SHOGI_MAINMENU_H

#include <QtWidgets/QWidget>

class MainMenuG: public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuG(QWidget *parent);

private slots:

    void exit();

};


#endif //SHOGI_MAINMENU_H
