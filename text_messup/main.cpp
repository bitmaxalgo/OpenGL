
#include <vector>
#include <iostream>

#include "oglhelper.h"
#include "text.h"

int main()
{
    ogl::init();
    GLFWwindow * window = ogl::window(800,600,"window");
    ogl::setcontext(window);
    ogl::loadglad(window);

    std::vector<float> zero_ndc = ogltext::generateMap(ogltext::NUM::ZERO);

    GLuint VAO = ogl::genbindVAO();
    GLuint VBO = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,2,zero_ndc);


    GLuint vshader = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("vshdr.glsl").data());
    GLuint fshader = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("fshdr.glsl").data());
    GLuint program = ogl::finishProgram(vshader,fshader);
    glUseProgram(program);


    std::vector<float> one_ndc = ogltext::generateMap(ogltext::NUM::ONE);
    GLuint VBAOO = ogl::genbindVAO();
    GLuint VBUF = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,2,one_ndc);

    GLuint onevshader = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("onevert.glsl").data());
    GLuint onefshader = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("onefrag.glsl").data());
    GLuint oneprogram = ogl::finishProgram(onevshader,onefshader);
    glUseProgram(oneprogram);
    glPointSize(25.0f);



    while (!glfwWindowShouldClose(window)) {
        ogl::setColor(1.0f,1.0f,1.0f,1.0f);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS,0,zero_ndc.size()/2);

        glUseProgram(oneprogram);
        glBindVertexArray(VBAOO);
        glDrawArrays(GL_POINTS,0,one_ndc.size()/2);

 

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);

    return 0;
}