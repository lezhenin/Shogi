#ifndef SHOGI_APPLICATION_H
#define SHOGI_APPLICATION_H

#include "Scenes/Scene.h"

class Application
{

public:
    explicit Application(Scene *scene = nullptr) : scene(scene) { }

    void start()
    {
        while (scene != nullptr)
        {
            scene->show();
            Scene *tmp = scene->getNextScene();
            delete scene;
            scene = tmp;
        }
    }

    virtual ~Application() { }

protected:
    Scene *scene;
};


#endif //SHOGI_APPLICATION_H
