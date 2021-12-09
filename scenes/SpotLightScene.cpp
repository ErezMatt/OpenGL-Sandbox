#include "SpotLightScene.h"

SpotLightScene::SpotLightScene(std::shared_ptr<SceneData> data)
    :_data(data)
{
    init();
}

void SpotLightScene::init()
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

    float groundSize = 100.0f;

    std::vector<unsigned int> groundIndices = {
         0, 2, 1,
         1, 2, 3
    };

    std::vector <Vertex> groundVertices = {
     {glm::vec3(-groundSize, 0.0f, -groundSize), glm::vec2(0.0f, 0.0f),             glm::vec3(0.0f, -1.0f, 0.0f)},
     {glm::vec3(groundSize, 0.0f, -groundSize), glm::vec2(groundSize, 0.0f),       glm::vec3(0.0f, -1.0f, 0.0f)},
     {glm::vec3(-groundSize, 0.0f,  groundSize), glm::vec2(0.0f, groundSize),       glm::vec3(0.0f, -1.0f, 0.0f)},
     {glm::vec3(groundSize, 0.0f,  groundSize), glm::vec2(groundSize, groundSize), glm::vec3(0.0f, -1.0f, 0.0f)}
    };

    Light::calculateAverageNormals(vertices, indices);

    auto obj1 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj1));

    auto obj2 = std::make_unique<Mesh>(vertices, indices);
    meshList.push_back(std::move(obj2));

    auto ground = std::make_unique<Mesh>(groundVertices, groundIndices);
    meshList.push_back(std::move(ground));

    shader.createFromFile(vShader, fShader);
    projection = glm::perspective(45.0f, _data->window.getBufferWidth() / _data->window.getBufferHeight(), 0.1f, 100.0f);
    model = glm::mat4(1.0f);

    shinyMaterial = Material(1.0f, 32);
    dullMaterial = Material(0.4f, 8);
    zMaterial = Material(0.0f, 1);

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    metalTexture = Texture("res/textures/metal.png");
    metalTexture.load();

    groundTexture = Texture("res/textures/ground.jpg");
    groundTexture.load();

    light = DirectionalLight(1.0f, 1.0f, 1.0f, 0.1f, 0.3f, 2.0f, -1.0f, -2.0f);
    color = light.getColor();
    color.r *= 255;
    color.g *= 255;
    color.b *= 255;
    intensity = light.getAmbientIntensity() * 255;


    shader.use();
    auto light1 = std::make_unique<PointLight>(0.0f, 1.0f, 0.0f, 0.5f, 0.8f, -4.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.3f);
    pLights.push_back(std::move(light1));

    auto light2 = std::make_unique<PointLight>(0.0f, 0.0f, 1.0f, 0.5f, 0.8f, 4.0f, 2.0f, 0.0f, 0.1f, 0.2f, 0.3f);
    pLights.push_back(std::move(light2));

    auto light3 = std::make_unique<PointLight>(1.0f, 0.0f, 0.0f, 0.5f, 0.8f, 0.0f, 2.0f, -4.0f, 0.1f, 0.2f, 0.3f);
    pLights.push_back(std::move(light3));

   
    auto slight1 = std::make_unique<SpotLight>(1.0f, 1.0f, 1.0f, 
        0.0f, 3.0f, 
        0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.f,
        0.0f, -1.0f, 0.0f,
        20.0f);
   

    
    sLights.push_back(std::move(slight1));

    auto slight2 = std::make_unique<SpotLight>(1.0f, 1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 5.5f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        20.0f);
    sLights.push_back(std::move(slight2));
    shader.setPointLights(std::move(pLights));
    shader.setSpotLights(std::move(sLights));
}

void SpotLightScene::update(float dT)
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

void SpotLightScene::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader.use();

   
    light.setColor({ color.x / 255, color.y / 255, color.z / 255 });
    light.setAmbientIntensity(intensity / 255);

    shader.setDirectionalLight(light);
    sLights[0]->setRay(glm::vec3(camera.getPosition().x, camera.getPosition().y - 0.3f, camera.getPosition().z), camera.getDirection());
    shader.setSpotLights(std::move(sLights));
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

    zMaterial.use(shader);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
    shader.SetUniformMat4f("model", model);
    groundTexture.use();
    meshList[2]->render();
}

void SpotLightScene::imGuiRender()
{
    ImGui::Checkbox("Camera Mode", &cameraMode);
    ImGui::Text("ESC to turn off Texture Mode");
    ImGui::SliderFloat("Red Intensity", &color.r, 0, 255);
    ImGui::SliderFloat("Green Intensity", &color.g, 0, 255);
    ImGui::SliderFloat("Blue Intensity", &color.b, 0, 255);
    ImGui::SliderFloat("Light Intensity", &intensity, 0, 255);
}

