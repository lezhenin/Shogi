#include <QtWidgets>
#include "MainMenuGUI.h"
#include "GameGUI.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainMenuG menu(0);
    menu.show();
    return app.exec();


}