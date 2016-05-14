#include <QtWidgets>
#include "MainMenuGUI.h"
#include "GameGUI.h"


int main(int argc, char *argv[])
{
    QTranslator translator;
    QApplication app(argc, argv);
    translator.load("translation_" + QLocale::system().name());
    app.installTranslator(&translator);
    MainMenuG menu(0);
    menu.show();
    qDebug() << "menu closed";
    return app.exec();
}