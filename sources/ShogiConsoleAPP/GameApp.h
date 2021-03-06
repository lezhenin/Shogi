#ifndef SHOGI_GAMEAPP_H
#define SHOGI_GAMEAPP_H


#include "Application.h"
#include "Scenes/MainMenu.h"
/**
 * @brief Игровое приложение
 *
 * Основной класс приложения, запускает отрисовку сцен.
 */
class GameApp : public Application
{
public:
    explicit GameApp(Scene *scene = new MainMenu()) : Application(scene) { }
};


#endif //SHOGI_GAMEAPP_H
