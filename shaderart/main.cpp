
#include <vector>
#include <iostream>

#include "oglhelper.h"

const int width = 1920;
const int height = 1080;

int main()
{
    ogl::init();
    GLFWwindow * window = ogl::window(width,height,"window");
    ogl::setcontext(window);
    ogl::loadglad(window);

    std::vector<float> background =  ogl::generateBackdrop();
    GLuint background_vao = ogl::genbindVAO();
    GLuint background_vbo = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,3,background);

    GLuint background_vshader = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("background_v.glsl").data());
    GLuint background_fshader = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("background_f.glsl").data());
    GLint background_program = ogl::finishProgram(background_vshader,background_fshader);

    GLint resolution_u_loc = glGetUniformLocation(background_program,"resolution");
    GLint time_u_loc = glGetUniformLocation(background_program,"time");

    glUseProgram(background_program); 
    glUniform2f(resolution_u_loc,1920,1080);
    glUniform1f(time_u_loc,glfwGetTime());

    while (!glfwWindowShouldClose(window)) {
        glUniform1f(time_u_loc,glfwGetTime());

        glUseProgram(background_program);
        glDrawArrays(GL_TRIANGLES,0,6);

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);

    return 0;
}