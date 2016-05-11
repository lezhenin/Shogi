#include <QtWidgets>
#include "MainMenuGUI.h"
#include "GameGUI.h"


int main(int argc, char *argv[])
{
    QTranslator translator;
    QApplication app(argc, argv);
    translator.load("translation_ru");
    app.installTranslator(&translator);
    MainMenuG menu(0);
    menu.show();
    return app.exec();
}