
#include <iostream>
#include <vector>
#include <fstream>

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "oglhelper.h"

void ogl::init() {
    if (!glfwInit())
    {
        std::cerr << "There was an error setting up GLFW." << "\n";
    } else std::cout << "GLFW initialized.\n";
}

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
}

void ogl::setcontext(GLFWwindow * window) {
    std::cout << "Window context set with pointer at: " << &window << "\n";
    glfwMakeContextCurrent(window);
}

void ogl::loadglad(GLFWwindow * window) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "There was an error loading function pointers.\nTerminating GLFW processes.";
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

float ogl::PI = 3.14159;

std::vector<float> ogl::generateBall(const int precision, float radius) {
    std::vector<float> ballshape;
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

void ogl::printvector(std::vector<float> &vec) {
    for (auto i : vec) {
        std::cout << i << std::endl;
    }
}

const std::string ogl::loadShaderSource(const char* filepath) {
    std::string container;
    std::ifstream file(filepath);    
    if (!file.is_open()) {
        std::cerr << "Error opening the file : " << filepath << "." << std::endl;
        return nullptr;
    } else {
        std::string line;
        while (getline(file,line))
        {
            container.append(line + "\n");            
        }
        file.close();
        return container;
    }
}

GLuint ogl::createShader(SHADER_TYPE typeofshader, const char * sourcecode) {
    GLuint shdr;
    if (typeofshader == VERTEX_SHADER) {
        shdr = glCreateShader(GL_VERTEX_SHADER);
    }
    if (typeofshader == FRAGMENT_SHADER) {
        shdr = glCreateShader(GL_FRAGMENT_SHADER);
    }
    glShaderSource(shdr,1,&sourcecode,nullptr);
    glCompileShader(shdr);
    GLint param;
    glGetShaderiv(shdr,GL_COMPILE_STATUS,&param);
    if (!param) {
        char infolog[512];
        glGetShaderInfoLog(shdr,512,nullptr,infolog);
        std::cerr << "Error compiling shader : " << infolog << std::endl;
    }
    return shdr;
}

GLint ogl::finishProgram(GLuint vertexshader, GLuint fragmentshader) {
    GLint program = glCreateProgram();
    glAttachShader(program,vertexshader);
    glAttachShader(program,fragmentshader);
    glLinkProgram(program);
    return program;
}


void ogl::basicEvents(GLFWwindow * window) {
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void ogl::setColor(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ogl::cleanUp(GLFWwindow * window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

std::vector<int> ogl::setUpBuffers(bool create_vao, bool create_vbo,  bool modify_vao, int index_to_bind, bool enable_vbo, int datum_size, BUFFER_TYPE data_type, std::vector<float> &data) {
    std::vector<int> objectnames;
    if (create_vao) {
        GLuint VAO;
        glGenVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        
        objectnames.push_back(VAO);
    } else objectnames.push_back(0);
    if (create_vbo) {
        GLuint VBO;
        glGenBuffers(1,&VBO);
        if (data_type == ARRAY_BUFFER) {
            glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(float),data.data(),GL_STATIC_DRAW);
        }
        if (modify_vao) {
            glVertexAttribPointer(index_to_bind,datum_size,GL_FLOAT,GL_FALSE,datum_size*sizeof(GL_FLOAT),(void*)(0));
            if (enable_vbo) {
                glEnableVertexAttribArray(index_to_bind);
            }
        }

        objectnames.push_back(VBO);
    } else objectnames.push_back(0);
    return objectnames;
}

GLuint ogl::genVAO() {
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    return VAO;
}


GLuint ogl::genVBO() {
    GLuint VBO;
    glGenBuffers(1,&VBO);
    return VBO;
}

GLuint ogl::genbindVBO() {
    GLuint VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    return VBO;
}

GLuint ogl::genbindVAO() {
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    return VAO;
}


void ogl::upload_point_enable_AB(const int index,const int datumsize,std::vector<float> &array) {
    glBufferData(GL_ARRAY_BUFFER,array.size()*sizeof(float),array.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(index,datumsize,GL_FLOAT,GL_FALSE,datumsize*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(index);
}


void ogl::resize(GLFWwindow * window,int width, int height) {
    glViewport(0,0,width,height);    
}

void ogl::framecb(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window,resize);
}

std::vector<float> ogl::generateBackdrop() {
    std::vector<float> backdrop = {
        -1.0f,-1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        1.0f,1.0f,0.0f,

        -1.0f,-1.0f,0.0f,
        -1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f
    };
    return backdrop;
}
