
#ifndef OGLHELPER_H
#define OGLHELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ogl {

    public:
    enum SHADER_TYPE {
        VERTEX_SHADER = 0,
        FRAGMENT_SHADER = 1
    };
    enum BUFFER_TYPE {
       ARRAY_BUFFER = 0, 
    };


    static void init();
    static GLFWwindow* window(int width,int height,const char* title);
    static void setcontext(GLFWwindow*);
    static void loadglad(GLFWwindow*);
    static std::vector<float> generateBall(const int precision, float radius);
    static std::vector<float> generateBackdrop();
    static float PI;
    static void printvector(std::vector<float> &vec);
    static const std::string loadShaderSource(const char* filepath);
    static GLuint createShader(SHADER_TYPE typeofshader, const char * sourcecode) ;
    static GLint finishProgram(GLuint vertexshader, GLuint fragmentshader);
    static void basicEvents(GLFWwindow * window);
    static void setColor(float r, float g, float b, float a);
    static void cleanUp(GLFWwindow* window);
    static std::vector<int> setUpBuffers(bool create_vao, bool create_vbo,  bool modify_vao, int index_to_bind, bool enable_vbo, int datum_size, BUFFER_TYPE data_type, std::vector<float> &data);
    static GLuint genVAO();
    static GLuint genbindVAO();
    static GLuint genVBO();
    static GLuint genbindVBO();
    static void upload_point_enable_AB(const int index,const int datumsize,std::vector<float> &array);
    static void resize(GLFWwindow * window, int width, int height);
    static void framecb(GLFWwindow * window);
};
#endif