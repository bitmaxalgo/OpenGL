
#ifndef OGLHELPER_H
#define OGLHELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ogl {
    public:
    static void init();
    static GLFWwindow* window(int width,int height,const char* title);
    static void setcontext(GLFWwindow*);
    static void loadglad(GLFWwindow*);
};
#endif