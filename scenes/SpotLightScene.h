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
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

class SpotLightScene : public Scene
{
public:
    const std::string vShader = "res/shaders/PointLight.vert";
    const std::string fShader = "res/shaders/SpotLight.frag";

public:
    SpotLightScene(std::shared_ptr<SceneData> data);
    virtual ~SpotLightScene() { std::cout << "Spot Light Scene"; }

    void init();
    void update(float dT) override;
    void render() override;
    void imGuiRender() override;
private:
    std::shared_ptr<SceneData> _data;

    Shader shader;
    Camera camera;
    Texture metalTexture;
    Texture groundTexture;
    DirectionalLight light;
    Material shinyMaterial;
    Material dullMaterial;
    Material zMaterial;

    std::vector<std::unique_ptr<Mesh>> meshList;
    std::vector<std::unique_ptr<PointLight>> pLights;
    std::vector<std::unique_ptr<SpotLight>> sLights;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 color;
    GLfloat intensity;

    bool cameraMode{ true };
    int rotation{ 0 };
};