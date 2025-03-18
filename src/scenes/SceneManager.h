#pragma once

#include <memory>
#include <stack>

#include "Scene.h"

class SceneManager
{
private:
    enum { NONE, ADDING, REMOVING } status;

public:
    SceneManager();
    virtual ~SceneManager();

    void addScene(std::unique_ptr<Scene> nScene, bool nReplacing = true);
    void eraseScene();
    void update();
    void clear();

    std::unique_ptr<Scene>& getScene();

private:
    std::stack<std::unique_ptr<Scene>> scenes;
    std::unique_ptr<Scene> newScene;
    bool replacing;
};