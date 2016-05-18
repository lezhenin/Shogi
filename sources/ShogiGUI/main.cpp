#include <QtWidgets>
#include "MenuWindow.h"
#include "GameWindow.h"


int main(int argc, char *argv[])
{
    QTranslator translator;
    QApplication app(argc, argv);
    translator.load("translation_" + QLocale::system().name());
    app.installTranslator(&translator);
    MenuWindow menu(0);
    menu.show();
    return app.exec();
}