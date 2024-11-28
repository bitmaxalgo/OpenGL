
#include <iostream>
#include <vector>
#include <cmath>

#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "oglhelper.h"

using std::vector;
using std::cout;
using std::cerr;
using std::string;


int main()
{
    ogl::init();
    GLFWwindow* window = ogl::window(800,600,"title");
    ogl::setcontext(window);
    ogl::loadglad(window);

    vector<float> ballshape = ogl::generateBall(32,0.5f);

    vector<int> vao_vbo = ogl::setUpBuffers(true,true,true,0,true,2,ogl::ARRAY_BUFFER,ballshape);

    GLuint vert_obj = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("vertex_shader.glsl").data());
    GLuint frag_obj = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("fragment_shader.glsl").data());
    GLint program = ogl::finishProgram(vert_obj,frag_obj);

    glUseProgram(program);

    while (!glfwWindowShouldClose(window))    
    {
        ogl::setColor(0.1f,0.2f,0.5f,1.0f);

        glDrawArrays(GL_TRIANGLE_FAN,0,ballshape.size()/2);

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);
}