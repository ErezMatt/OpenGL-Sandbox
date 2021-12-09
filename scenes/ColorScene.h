#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class ColorScene : public Scene
{
public:
    ColorScene(std::shared_ptr<SceneData> data);
    virtual ~ColorScene() { std::cout << "Color Scene"; }

    void render() override;
    void imGuiRender() override;
private:
    std::shared_ptr<SceneData> _data;
    float backgroundColor[3];
};