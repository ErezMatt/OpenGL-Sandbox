#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <memory>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

#include "scenes/SceneManager.h"

struct SceneData
{
	Window window;
	SceneManager sceneManager;
};

class Application
{
public:
	Application();
	Application(int width, int height);
	~Application();

	void run();
	void update();

private:
	std::shared_ptr<SceneData> _data{ std::make_shared<SceneData>() };
};