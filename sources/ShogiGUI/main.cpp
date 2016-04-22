#include <QtWidgets>
#include "MainMenuG.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainMenuG menu(0);
    menu.resize(800,600);
    menu.show();
    return app.exec();
}