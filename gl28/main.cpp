
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

const float PI = 3.14159;

void printBallverts(vector<float> &ballshape);
vector<float> generateBall(const int precision, float radius);

void processKeypress(GLFWwindow * window);

enum SHADER_TYPE {
    VERTEX_SHADER = 0,
    FRAGMENT_SHADER = 1
};

GLuint createShader(SHADER_TYPE typeofshader, const char * sourcecode);
const string loadShader(const char* filepath);
GLint finishProgram(GLuint vertexshader, GLuint fragmentshader);






int main()
{
    ogl::init();
    GLFWwindow* window = ogl::window(800,600,"title");
    ogl::setcontext(window);
    ogl::loadglad(window);

    vector<float> ballshape = generateBall(32,0.5f);

    GLuint VBO;
    glGenBuffers(1,&VBO);
    
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*ballshape.size(),ballshape.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);



    GLuint vert_obj = createShader(VERTEX_SHADER,loadShader("vertex_shader.glsl").data());
    GLuint frag_obj = createShader(FRAGMENT_SHADER,loadShader("fragment_shader.glsl").data());
    GLint program = finishProgram(vert_obj,frag_obj);

    glUseProgram(program);

    while (!glfwWindowShouldClose(window))    
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f,0.1f,0.2f,1.0f);

        glDrawArrays(GL_TRIANGLE_FAN,0,ballshape.size()/2);

        processKeypress(window);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void processKeypress(GLFWwindow * window) {
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
}

const string loadShader(const char* filepath) {
    string container;
    std::ifstream file(filepath);    
    if (!file.is_open()) {
        cerr << "Error opening the file : " << filepath << "." << std::endl;
        return nullptr;
    } else {
        string line;
        while (getline(file,line))
        {
            container.append(line);            
        }
        file.close();
        return container;
    }
}

GLuint createShader(SHADER_TYPE typeofshader, const char * sourcecode) {
    GLuint shdr_object_ptr;
    if (typeofshader == VERTEX_SHADER) {
        shdr_object_ptr = glCreateShader(GL_VERTEX_SHADER);
    }
    if (typeofshader == FRAGMENT_SHADER) {
        shdr_object_ptr = glCreateShader(GL_FRAGMENT_SHADER);
    }
    glShaderSource(shdr_object_ptr,1,&sourcecode,nullptr);
    glCompileShader(shdr_object_ptr);
    return shdr_object_ptr;
}

vector<float> generateBall(const int precision, float radius) {

    vector<float> ballshape;
    int prec = precision;
    float step = 2*PI / (float)prec;
    ballshape.push_back(0.0f);
    ballshape.push_back(0.0f);
    
    for (int i = 0; i <= precision; i ++) {
        float cosp = cosf(i*step) * radius;
        float sinp = sinf(i*step) * radius;

        ballshape.push_back(cosp);
        ballshape.push_back(sinp);
    }
    return ballshape;
}

void printBallverts(vector<float> &ballshape) {
    for (auto i : ballshape) {
        cout << i << std::endl;
    }
}

GLint finishProgram(GLuint vertexshader, GLuint fragmentshader) {
    GLint program = glCreateProgram();
    glAttachShader(program,vertexshader);
    glAttachShader(program,fragmentshader);
    glLinkProgram(program);
    return program;
}