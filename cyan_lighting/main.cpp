
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "oglhelper.h"

#ifndef WIDTH_C
#define WIDTH_C 800
#endif

#ifndef HEIGHT_C
#define HEIGHT_C 600
#endif

#define BACKDROP_C 0.0f,1.0f,1.0f

#include "tests.h"

using std::vector;
struct screeninfo {
    int width_var = WIDTH_C;
    int w_loc;
    int height_var = HEIGHT_C;
    int h_loc;
};


int main() {
    ogl::init();
    GLFWwindow * window = ogl::window(WIDTH_C,HEIGHT_C,"Window");
    ogl::setcontext(window);
    ogl::loadglad(window);

    screeninfo windowinfo;

    vector<float> backdrop = {
        -1.0f,-1.0f, BACKDROP_C,
         1.0f,-1.0f, BACKDROP_C,
         1.0f, 1.0f, BACKDROP_C,
        -1.0f, 1.0f, BACKDROP_C,
    };

    vector<unsigned int> indices {
        0,1,2,
        0,2,3,
    };

    GLuint VBO,VAO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(GL_ARRAY_BUFFER, backdrop.size()*sizeof(float), backdrop.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(0));
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(2*sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    const char* vsource = R"(
    #version 330 core

    layout (location = 0) in vec2 position; 
    layout (location = 1) in vec3 color; 

    out vec3 colorout;

    void main()
    {
        gl_Position = vec4(position, 0.0f, 1.0f); 
        colorout = color;
    }
    )";

    const char* fsource = R"(
    #version 330 core

    in vec3 colorout;
    out vec4 finalcolor; 

    uniform float width;
    uniform float height;

    vec4 test = vec4(width,height,0.0f,1.0f);

    float intensity = 100 / length(test - gl_FragCoord);

    void main()
    {
        finalcolor = vec4(colorout, 1.0f) * intensity; 
    }
    )";

    GLuint vshader, fshader, program;
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    program = glCreateProgram();

    glShaderSource(vshader,1,&vsource,nullptr);
    glShaderSource(fshader,1,&fsource,nullptr);

    glCompileShader(vshader);
    glCompileShader(fshader);

    glAttachShader(program,vshader);
    glAttachShader(program,fshader);

    glLinkProgram(program);
    GLint height_loc = glGetUniformLocation(program,"height");
    windowinfo.h_loc = height_loc;
    GLint width_loc = glGetUniformLocation(program,"width");
    windowinfo.w_loc = width_loc;


    glfwSetWindowUserPointer(window,&windowinfo);


    glUseProgram(program);

    glfwSetFramebufferSizeCallback(window, framebuffercb);
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processEvents(window);


        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();        
    }
};

void updateUniforms(GLint wloc, GLint hloc, int width, int height) {
   glUniform1f(hloc,height);
   glUniform1f(wloc,width);
};

void framebuffercb(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
    screeninfo* myinfo = (screeninfo*)glfwGetWindowUserPointer(window);
    myinfo->width_var = (float)(width/2.0f);
    myinfo->height_var = (float)(height/2.0f);

    glUniform1f(myinfo->h_loc,myinfo->height_var);
    glUniform1f(myinfo->w_loc,myinfo->width_var);
}


void processEvents(GLFWwindow * window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
}