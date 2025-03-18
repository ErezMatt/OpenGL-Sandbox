#include "CircleScene.h"

CircleScene::CircleScene(std::shared_ptr<SceneData> data)
    :_data(data)
{
    init();
}

void CircleScene::init()
{
    segments = 4;
    polygon = std::make_unique<Polygon>(_data->window.getBufferWidth()/2, _data->window.getBufferHeight()/2, 150, segments);

    shader.createFromFile(vShader, fShader);
    projection = glm::ortho(0.0f, _data->window.getBufferWidth(), 0.0f, _data->window.getBufferHeight(), -1.0f, 1.0f);
    model = glm::mat4(1.0f);
}

void CircleScene::update(float dT)
{

}

void CircleScene::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    

    model = glm::mat4(1.0f);
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("projection", projection);
    polygon->render();

}

void CircleScene::imGuiRender()
{
    if (ImGui::SliderInt("Number of vertexes", &segments, 3, 50))
    {
        polygon = std::make_unique<Polygon>(_data->window.getBufferWidth() / 2, _data->window.getBufferHeight() / 2, 150, segments);
    }
}
