#include "SphereScene.h"

SphereScene::SphereScene(std::shared_ptr<SceneData> data)
    :_data(data)
{
    init();
}

void SphereScene::init()
{  
    auto sphere1 = std::make_unique<Sphere>(0.0f, 0.0f, 0.0f, 0.5f, 400, 400);
    sphereList.push_back(std::move(sphere1));


    shader.createFromFile(vShader, fShader);
    projection = glm::perspective(45.0f, _data->window.getBufferWidth() / _data->window.getBufferHeight(), 0.1f, 100.0f);
    model = glm::mat4(1.0f);

    shinyMaterial = Material(1.0f, 64);
    dullMaterial = Material(0.2f, 4);

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    metalTexture = Texture("res/textures/fullmapb.png");
    metalTexture.load();

    light = DirectionalLight(1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, -1.0f, -2.0f);
    color = light.getColor();
    color.r *= 255;
    color.g *= 255;
    color.b *= 255;
    intensity = light.getAmbientIntensity() * 255;
}

void SphereScene::update(float dT)
{
    if (rotation >= 360)
        rotation -= 360;
    ++rotation;

    if (_data->window.getKey(GLFW_KEY_ESCAPE)) {
        _data->window.resetKey(GLFW_KEY_ESCAPE);
        _data->window.reset();
        cameraMode = false;
    }

    if (cameraMode)
        _data->window.createCallbacks();
    else
        _data->window.destroyCallbacks();


    camera.keyControl(_data->window, dT);
    camera.mouseControl(_data->window.getXChange(), _data->window.getYChange());
}

void SphereScene::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader.use();


    light.setColor({ color.x / 255, color.y / 255, color.z / 255 });
    light.setAmbientIntensity(intensity / 255);

    shader.setDirectionalLight(light);

    shader.SetUniform3f("cameraPosition", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 0.0f, -2.5f));
    model = glm::rotate(model, glm::radians((float)(360 - rotation)), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("view", camera.calculateViewMatrix());
    shader.SetUniformMat4f("projection", projection);
    shinyMaterial.use(shader);
    metalTexture.use();
    sphereList[0]->render(); 
    
    
    
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, 0.0f, -2.5f));
    model = glm::rotate(model, glm::radians((float)(rotation)), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("view", camera.calculateViewMatrix());
    shader.SetUniformMat4f("projection", projection);
    dullMaterial.use(shader);
    metalTexture.use();
    sphereList[0]->render();
}

void SphereScene::imGuiRender()
{
    ImGui::Checkbox("Texture Mode", &cameraMode);
    ImGui::Text("ESC to turn off Texture Mode");
    ImGui::SliderFloat("Red Intensity", &color.r, 0, 255);
    ImGui::SliderFloat("Green Intensity", &color.g, 0, 255);
    ImGui::SliderFloat("Blue Intensity", &color.b, 0, 255);
    ImGui::SliderFloat("Light Intensity", &intensity, 0, 255);
}

