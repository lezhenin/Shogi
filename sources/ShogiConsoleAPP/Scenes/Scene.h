#ifndef SHOGI_SCENE_H
#define SHOGI_SCENE_H

class Scene
{
public:
    virtual void show() = 0;
    Scene *getNextScene()
    {
        return next;
    }

    virtual ~Scene() { }

protected:
    Scene *next = nullptr;
};


#endif //SHOGI_SCENE_H
