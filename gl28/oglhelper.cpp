
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "oglhelper.h"

void ogl::init() {
    if (!glfwInit())
    {
        std::cerr << "There was an error setting up GLFW." << "\n";
    } else std::cout << "GLFW initialized.\n";
};

GLFWwindow* ogl::window(int width, int height, const char * title) {
    GLFWwindow * window = glfwCreateWindow(width,height,title,nullptr,nullptr);
    if (!window)
    {
        std::cerr << "Error creating a GLFW window. Terminating GLFW.";
        glfwTerminate();
        return nullptr;
    } else {
        std::cout << "GLFW window created.\n";
        return window;
    }
};

void ogl::setcontext(GLFWwindow * window) {
    std::cout << "Window context set with pointer at: " << &window << "\n";
    glfwMakeContextCurrent(window);
};

void ogl::loadglad(GLFWwindow * window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "There was an error loading function pointers.\nTerminating GLFW processes.";
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};