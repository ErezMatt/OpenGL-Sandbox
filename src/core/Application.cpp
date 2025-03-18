#include "Application.h"
#include "scenes/ColorScene.h"
#include "scenes/MenuScene.h"

Application::Application()
{
    _data->window = Window(800, 600);
    _data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<MenuScene>(_data)));
}
Application::Application(int width, int height)
{
    _data->window = Window(width, height);
    _data->sceneManager.addScene(std::unique_ptr<Scene>(std::make_unique<MenuScene>(_data)));
}

Application::~Application()
{

    _data->sceneManager.clear();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run()
{
    _data->window.init();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(_data->window.getWindow(), true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    update();
}

void Application::update()
{  
    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = 0.0f;

    while (!_data->window.shouldClose())
    {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glfwPollEvents();
        _data->sceneManager.update();

        _data->sceneManager.getScene()->update(deltaTime);
        _data->sceneManager.getScene()->render();
        

        ImGui::Begin("Menu");
        {
            if (typeid(MenuScene) != typeid(*_data->sceneManager.getScene()) && ImGui::Button("<-"))
            {
               // _data->window.destroyCallbacks();
                _data->sceneManager.eraseScene();
            }
        }

        _data->sceneManager.getScene()->imGuiRender();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        _data->window.swapBuffers();
    }
}
