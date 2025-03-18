#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Polygon.h"

class ShaderCircleScene : public Scene
{
public:
    const std::string vShader = "res/shaders/CircleShader.vert";
    const std::string fShader = "res/shaders/CircleShader.frag";
public:
    ShaderCircleScene(std::shared_ptr<SceneData> data);
    virtual ~ShaderCircleScene() { std::cout << "Circle Scene"; }

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

    int rotation{0};
    float canvasWidth;
    float canvasHeight;
    float scale{ 1.0f };
    float time{ 0.0f };
    bool timeNeeded{ false };
};