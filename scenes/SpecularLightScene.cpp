#include "SpecularLightScene.h"

SpecularLightScene::SpecularLightScene(std::shared_ptr<SceneData> data)
    :_data(data)
{
    init();
}

void SpecularLightScene::init()
{
    std::vector<unsigned int> indices = {
          0, 3, 1,
          1, 3, 2,
          2, 3, 0,
          0, 1, 2
    };

    std::vector <Vertex> vertices = {
        {glm::vec3(-1.0f, -1.0f, -0.6f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        {glm::vec3(0.0f, -1.0f, 1.0f), glm::vec2(0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, -0.6f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)}
    };

    Light::calculateAverageNormals(vertices, indices);
    auto obj1 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj1));

    auto obj2 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj2));

    shader.createFromFile(vShader, fShader);
    projection = glm::perspective(45.0f, _data->window.getBufferWidth() / _data->window.getBufferHeight(), 0.1f, 100.0f);
    model = glm::mat4(1.0f);

    shinyMaterial = Material(1.0f, 32);
    dullMaterial = Material(0.4f, 8);

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    metalTexture = Texture("res/textures/metal.png");
    metalTexture.load();

    light = DirectionalLight(1.0f, 1.0f, 1.0f, 0.3f, 1.0f, 2.0f, -1.0f, -2.0f);
    color = light.getColor();
    color.r *= 255;
    color.g *= 255;
    color.b *= 255;
    intensity = light.getAmbientIntensity() * 255;
}

void SpecularLightScene::update(float dT)
{
    if (rotation >= 360)
        rotation -= 360;
    ++rotation;

    if (_data->window.getKey(GLFW_KEY_ESCAPE)) {
        _data->window.resetKey(GLFW_KEY_ESCAPE);
        _data->window.reset();
        cameraMode = false;
    }

    if (cameraMode) {
        _data->window.disableCursor();
        camera.keyControl(_data->window, dT);
        camera.mouseControl(_data->window.getXChange(), _data->window.getYChange());
    }
    else {
        _data->window.enableCursor();
    }
}

void SpecularLightScene::render()
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
    model = glm::rotate(model, glm::radians((float)(rotation)), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("view", camera.calculateViewMatrix());
    shader.SetUniformMat4f("projection", projection);
    shinyMaterial.use(shader);
    metalTexture.use();
    meshList[0]->render();

    dullMaterial.use(shader);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.5f, 0.0f, -2.5f));
    model = glm::rotate(model, glm::radians((float)(360 - rotation)), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    meshList[1]->render();
}

void SpecularLightScene::imGuiRender()
{
    ImGui::Checkbox("Camera Mode", &cameraMode);
    ImGui::Text("ESC to turn off Texture Mode");
    ImGui::SliderFloat("Red Intensity", &color.r, 0, 255);
    ImGui::SliderFloat("Green Intensity", &color.g, 0, 255);
    ImGui::SliderFloat("Blue Intensity", &color.b, 0, 255);
    ImGui::SliderFloat("Light Intensity", &intensity, 0, 255);
}

