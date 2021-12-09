#include "CameraScene.h"

CameraScene::CameraScene(std::shared_ptr<SceneData> data)
    :_data(data)
{
    init();
}

void CameraScene::init()
{
    std::vector<unsigned int> indices = {
          0, 3, 1,
          1, 3, 2,
          2, 3, 0,
          0, 1, 2
    };

    std::vector <Vertex> vertices = {
        {glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(0.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        {glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
    };

    auto obj1 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj1));

    auto obj2 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj2));

    shader.createFromFile(vShader, fShader);
    projection = glm::perspective(45.0f, _data->window.getBufferWidth() / _data->window.getBufferHeight(), 0.1f, 100.0f);
    model = glm::mat4(1.0f);

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
}

void CameraScene::update(float dT)
{
    if (rotation >= 360)
        rotation -= 360;
    ++rotation;


    if (_data->window.getKey(GLFW_KEY_ESCAPE)) {
        _data->window.resetKey(GLFW_KEY_ESCAPE);
        _data->window.reset();
        cameraMode = false;
    }

    if(cameraMode)
        _data->window.createCallbacks();
    else
        _data->window.destroyCallbacks();

    camera.keyControl(_data->window, dT);
    camera.mouseControl(_data->window.getXChange(), _data->window.getYChange());
}

void CameraScene::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -2.5f));
    model = glm::rotate(model, glm::radians((float)rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("view", camera.calculateViewMatrix());
    shader.SetUniformMat4f("projection", projection);
    meshList[0]->render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
    model = glm::rotate(model, glm::radians((float)(360 - rotation)), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
    shader.SetUniformMat4f("model", model);
    meshList[1]->render();
}

void CameraScene::imGuiRender()
{
    ImGui::Checkbox("Camera Mode", &cameraMode);
    ImGui::Text("ESC to turn off Camera Mode");
}
