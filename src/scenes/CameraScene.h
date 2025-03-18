#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Camera.h"

class CameraScene : public Scene
{
public:
    const std::string vShader = "res/shaders/Camera.vert";
    const std::string fShader = "res/shaders/Basic.frag";

public:
    CameraScene(std::shared_ptr<SceneData> data);
    virtual ~CameraScene() { std::cout << "Camera Scene"; }

    void init();
    void update(float dT) override;
    void render() override;
    void imGuiRender() override;
private:
    std::shared_ptr<SceneData> _data;

    Shader shader;
    Camera camera;
    std::vector<std::unique_ptr<Mesh>> meshList;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    bool cameraMode{ true };
    int rotation{ 0 };
};