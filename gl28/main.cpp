
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

    vector<float> ballshape = ogl::generateBall(100,0.5f);

    GLuint VAO = ogl::genbindVAO();
    GLuint VBO = ogl::genbindVBO();

    ogl::upload_point_enable_AB(0,2,ballshape);

    GLuint vert_obj = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("ballshader_vert.glsl").data());
    GLuint frag_obj = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("ballshader_frag.glsl").data());
    GLint program = ogl::finishProgram(vert_obj,frag_obj);



    while (!glfwWindowShouldClose(window))    
    {
        ogl::setColor(0.1f,0.2f,0.5f,1.0f);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLE_FAN,0,ballshape.size()/2);

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);
}