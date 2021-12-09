#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	~Window();

	int init();

	GLfloat getBufferWidth() const { return bufferWidth; }
	GLfloat getBufferHeight() const { return bufferHeight; }
	bool getKey(unsigned int keyNum) const;
	GLfloat getXChange();
	GLfloat getYChange();
	GLFWwindow* getWindow() { return window; }

	bool shouldClose() const { return glfwWindowShouldClose(window); }

	void swapBuffers() { glfwSwapBuffers(window); }

	void resetKey(unsigned int keyNum);
	void reset();

	void createCallbacks();
	void destroyCallbacks();

private:
	GLFWwindow* window;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	static const int NUMBER_OF_KEYS = 1024;
	bool keys[NUMBER_OF_KEYS];
	
	GLfloat lastX{ 0.0f };
	GLfloat lastY{ 0.0f };
	GLfloat xChange{ 0.0f };
	GLfloat yChange{ 0.0f };
	bool mouseFirstMoved{ false };

private:
	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow *window, double xPos, double yPos);
};

