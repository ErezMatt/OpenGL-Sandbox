#pragma once

#include <memory>
#include <iostream>
#include "Scene.h"
#include "Application.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Sphere.h"

class SphereScene : public Scene
{
public:
    const std::string vShader = "res/shaders/SpecularLight.vert";
    const std::string fShader = "res/shaders/SphereScene.frag";

public:
    SphereScene(std::shared_ptr<SceneData> data);
    virtual ~SphereScene() { std::cout << "Diffuse Light Scene"; }

    void init();
    void update(float dT) override;
    void render() override;
    void imGuiRender() override;
private:
    std::shared_ptr<SceneData> _data;

    Shader shader;
    Camera camera;
    Texture metalTexture;
    DirectionalLight light;
    Material shinyMaterial;
    Material dullMaterial;

    std::vector<std::unique_ptr<Sphere>> sphereList;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 color;
    GLfloat intensity;

    bool cameraMode{ true };
    int rotation{ 0 };
};