#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class MenuScene : public Scene
{
public:
    MenuScene(std::shared_ptr<SceneData> data);
    virtual ~MenuScene() { std::cout << "Menu Scene"; }

    void render() override;
    void imGuiRender() override;
private:
    std::shared_ptr<SceneData> _data;
};