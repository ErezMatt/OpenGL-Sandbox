#include "SceneManager.h"

SceneManager::SceneManager()
{
}

void SceneManager::addScene(std::unique_ptr<Scene> nScene, bool nSeplacing)
{
    status = ADDING;
    replacing = replacing;
    newScene = std::move(nScene);
}

void SceneManager::eraseScene()
{
    status = REMOVING;
}

void SceneManager::clear()
{
    while (!scenes.empty()) {
        scenes.pop();
    }
}
void SceneManager::update()
{
    if (status == REMOVING && !scenes.empty()) {
        scenes.pop();
        status = NONE;
    }

    if (status == ADDING) {
        if (!scenes.empty()) {
            if (replacing) {
                scenes.pop();
            }
        
        }
        scenes.push(std::move(newScene));
        status = NONE;
    }
}

std::unique_ptr<Scene>& SceneManager::getScene()
{
    return scenes.top();
}

SceneManager::~SceneManager()
{
    clear();
}