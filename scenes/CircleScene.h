#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Polygon.h"

class CircleScene : public Scene
{
public:
    const std::string vShader = "res/shaders/Basic.vert";
    const std::string fShader = "res/shaders/Basic.frag";
public:
    CircleScene(std::shared_ptr<SceneData> data);
    virtual ~CircleScene() { std::cout << "Circle Scene"; }

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

    std::unique_ptr<Polygon> polygon;
    int segments;
    int rotation{ 0 };
};