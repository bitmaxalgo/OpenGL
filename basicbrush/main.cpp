
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


void processEvents(GLFWwindow * window, vector<Circle> &container);
void createCircle(double x, double y, vector<Circle> &container);
double xpos,ypos;
float width_g = 800.0f;
float height_g = 600.0f;

void framebc(GLFWwindow * window, int width, int height);

int main()
{
    ogl::init();
    GLFWwindow* window = ogl::window(width_g,height_g,"title");
    ogl::setcontext(window);
    ogl::loadglad(window);

    vector<Circle> circ_container;
    vector<float> circle_shape = ogl::generateBall(100,0.10);

    GLuint VAO_1 = ogl::genbindVAO();
    GLuint VBO_1 = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,2,circle_shape);    

    GLuint VS_1 = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("ballshader_vert.glsl").data());
    GLuint FS_1 = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("ballshader_frag.glsl").data());
    GLint PG_1 = ogl::finishProgram(VS_1,FS_1);
    glUseProgram(PG_1);

    GLint xloc = glGetUniformLocation(PG_1,"xpos");
    GLint yloc = glGetUniformLocation(PG_1,"ypos");

    glfwSetFramebufferSizeCallback(window,framebc);

    while (!glfwWindowShouldClose(window))    
    {
        ogl::setColor(0.2f,0.2f,0.2f,1.0f);
        processEvents(window,circ_container);

        if (circ_container.size() > 0) {
            for (int i = 0; i < circ_container.size(); i++) {
                Circle current = circ_container.at(i);
                glUniform1f(xloc,current.x);
                glUniform1f(yloc,current.y);
                glDrawArrays(GL_TRIANGLE_FAN,0,circle_shape.size()/2);
            }
        }

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);
}

void framebc(GLFWwindow * window, int width, int height) {
    glViewport(0,0,width,height);
    width_g = width;
    height_g = height;
}

void processEvents(GLFWwindow* window, vector<Circle> &container) {
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwGetCursorPos(window,&xpos,&ypos);
        createCircle(xpos,ypos,container);
        cout << xpos << " " << ypos << "\n";
    }
}

void createCircle(double x, double y, vector<Circle> &container) {
    float newx = (x / (width_g/2.0f)) - 1.0f;
    float newy = (y / (height_g/2.0f)) - 1.0f;
    Circle circle(newx,newy);
    container.push_back(circle);
}
