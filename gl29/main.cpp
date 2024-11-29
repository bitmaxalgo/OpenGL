
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

const float radius = 0.04f;

void processBoundaries(float radius, float &xspeed, float &xoff, int xoff_u, int xoffnew_u);

int main()
{
    ogl::init();
    GLFWwindow* window = ogl::window(800,600,"title");
    ogl::setcontext(window);
    ogl::loadglad(window);

                                                            // BALL
    vector<float> ballshape = ogl::generateBall(100,radius);
    GLuint VAO = ogl::genbindVAO();
    GLuint VBO = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,2,ballshape);
    GLuint vert_obj = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("ballshader_vert.glsl").data());
    GLuint frag_obj = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("ballshader_frag.glsl").data());
    GLint program = ogl::finishProgram(vert_obj,frag_obj);

    GLint xoff_u = glGetUniformLocation(program,"xoff");
    float xoff = 0.0f;
    glUniform1f(xoff_u,xoff);
    

    vector<float> backdrop = ogl::generateBackdrop();
    GLuint backdropVAO = ogl::genbindVAO();
    GLuint backdropVBO = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,3,backdrop);
    GLuint vshad_bdrop = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("backshader_vert.glsl").data());
    GLuint fshad_bdrop = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("backshader_frag.glsl").data());
    GLint backdrop_progam = ogl::finishProgram(vshad_bdrop,fshad_bdrop);

    GLint xoffnew_u = glGetUniformLocation(backdrop_progam,"xoffnew");
    glUniform1f(xoffnew_u,xoff);

    ogl::framecb(window);

    float xspeed = 0.01f;

    while (!glfwWindowShouldClose(window))    
    {
        ogl::setColor(0.2f,0.2f,0.2f,1.0f);

        glUseProgram(backdrop_progam);
        glBindVertexArray(backdropVAO);
        glDrawArrays(GL_TRIANGLES,0,6);
        glUniform1f(xoffnew_u,xoff);

        glUseProgram(program);
        glBindVertexArray(VAO);
        processBoundaries(radius,xspeed,xoff, xoff_u,xoffnew_u); 
        glDrawArrays(GL_TRIANGLE_FAN,0,ballshape.size()/2);
        glUniform1f(xoff_u,xoff);

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);
}

void processBoundaries(float radius, float &xspeed, float &xoff, int xoff_u, int xoffnew_u) {
        float radoff = 1.0f - radius;
        if (xoff > radoff) {
            xoff = radoff;
            xspeed *= -1;
        }

        if (xoff < -radoff) {
            xoff = -radoff;
            xspeed *= -1;
        }

        xoff += xspeed;

}