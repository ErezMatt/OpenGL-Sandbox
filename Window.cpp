#include "Window.h"

Window::Window() :
    window{ nullptr },
    width{ 800 },
    height{ 600 }
{
    for (size_t i = 0; i < NUMBER_OF_KEYS; ++i) {
        keys[i] = 0;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight) :
    window{ nullptr },
    width{ windowWidth },
    height{ windowHeight }
{
    for (size_t i = 0; i < NUMBER_OF_KEYS; ++i) {
        keys[i] = 0;
    }
}

Window::~Window()
{
    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();
}

int Window::init()
{
    if (!glfwInit()) {
        std::cout << "GLFW init failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "Sandbox Window", NULL, NULL);
    if (!window) {
        std::cout << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init failed" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(this->window, this);

    createCallbacks();

    return 0;
}

bool Window::getKey(unsigned int keyNum) const
{
    if (keyNum >= 0 && keyNum < NUMBER_OF_KEYS)
        return keys[keyNum];
    return false;
}

void Window::resetKey(unsigned int keyNum)
{
    if (keyNum >= 0 && keyNum < NUMBER_OF_KEYS)
        keys[keyNum] = false;
}

void Window::reset()
{
    lastX = 0.0f;
    lastY = 0.0f;
    xChange = 0.0f;
    yChange = 0.0f;
    mouseFirstMoved = false;
}

GLfloat Window::getXChange()
{
    GLfloat change = xChange;
    xChange = 0.0f;
    return change;
}

GLfloat Window::getYChange()
{
    GLfloat change = yChange;
    yChange = 0.0f;
    return change;
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(window, handleKeys);
    glfwSetCursorPosCallback(window, handleMouse);
}

void Window::destroyCallbacks()
{
    glfwSetKeyCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
}

void Window::enableCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::disableCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window* newWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (newWindow) {
        if (key >= 0 && key < NUMBER_OF_KEYS) {
            if (action == GLFW_PRESS) {
                newWindow->keys[key] = true;
            }
            else if(action == GLFW_RELEASE) {
                newWindow->keys[key] = false;
            }
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* newWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (newWindow) {
        if (!newWindow->mouseFirstMoved) {
            newWindow->lastX = xPos;
            newWindow->lastY = yPos;
            newWindow->mouseFirstMoved = true;
        }

        newWindow->xChange = xPos - newWindow->lastX;
        newWindow->yChange = newWindow->lastY - yPos;

        newWindow->lastX = xPos;
        newWindow->lastY = yPos;
    }
}
