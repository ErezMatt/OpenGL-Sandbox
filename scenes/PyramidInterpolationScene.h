#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class PyramidInterpolationScene : public Scene
{
public:
    const std::string vShader = "res/shaders/Basic.vert";
    const std::string fShader = "res/shaders/Basic.frag";
public:
    PyramidInterpolationScene(std::shared_ptr<SceneData> data);
    virtual ~PyramidInterpolationScene() { std::cout << "PyramidInterpolation Scene"; }

    void init();
    void update(float dT) override;
    void render() override;
    void imGuiRender() override;
private:
    std::shared_ptr<SceneData> _data;

    Shader shader;
    std::vector<std::unique_ptr<Mesh>> meshList;

    glm::mat4 model;
    glm::mat4 projection;

    int rotation { 0 };
};