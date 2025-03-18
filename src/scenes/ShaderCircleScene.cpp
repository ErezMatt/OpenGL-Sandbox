#include "ShaderCircleScene.h"

ShaderCircleScene::ShaderCircleScene(std::shared_ptr<SceneData> data)
    :_data(data)
{
    init();
}

void ShaderCircleScene::init()
{
    canvasWidth = _data->window.getBufferWidth();
    canvasHeight = _data->window.getBufferHeight();

    std::vector<unsigned int> indices = {
        0, 3, 1,
        3, 2, 1,
    };

    std::vector <Vertex> vertices = {
        {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        {glm::vec3(0.0f, canvasHeight, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        {glm::vec3(canvasWidth, canvasHeight, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        {glm::vec3(canvasWidth, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)}
    };
    auto obj1 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj1));

    shader.createFromFile(vShader, fShader);
    projection = glm::ortho(0.0f, _data->window.getBufferWidth(), 0.0f, _data->window.getBufferHeight(), -1.0f, 1.0f);
    model = glm::mat4(1.0f);
}

void ShaderCircleScene::update(float dT)
{
    time += dT;
}

void ShaderCircleScene::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.SetUniform3f("resolution", canvasWidth, canvasHeight, 0.0f);
    if(timeNeeded)
        shader.SetUniform1f("time", time);


    model = glm::mat4(1.0f);
    shader.SetUniformMat4f("model", model);
    shader.SetUniformMat4f("projection", projection);
    meshList[0]->render();

}

void ShaderCircleScene::imGuiRender()
{
    if (ImGui::Button("Circle"))
    {
        shader.clear();
        timeNeeded = false;
        shader.createFromFile(vShader, "res/shaders/CircleShader.frag");
    }

    if (ImGui::Button("Heart"))
    {
        shader.clear();
        timeNeeded = false;
        shader.createFromFile(vShader, "res/shaders/Heart.frag");
    }

    if (ImGui::Button("Face"))
    {
        shader.clear();
        timeNeeded = false;
        shader.createFromFile(vShader, "res/shaders/Face.frag");
    }   
    
    if (ImGui::Button("Colorful Heart"))
    {
        shader.clear();
        timeNeeded = true;
        shader.createFromFile(vShader, "res/shaders/ColorfulHeart.frag");
    }

    if (ImGui::Button("TV Noise"))
    {
        shader.clear();
        timeNeeded = true;
        shader.createFromFile(vShader, "res/shaders/TVNoise.frag");
    }
}
