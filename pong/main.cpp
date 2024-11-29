
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

void processBoundaries(float radius, float &xspeed, float &xoff, int xoff_u_loc, int xoffnew_u);

class Paddle {




    public:
    constexpr static float paddle_speed{0.01f};

    constexpr static float paddle_height{0.4f};
    constexpr static float paddle_width{0.05f};

    constexpr static float paddle_upper_boundary{1.0f - (paddle_height / 2.0f)};
    constexpr static float paddle_lower_boundary{-1.0f + (paddle_height / 2.0f)};

    float yoff;
    Paddle(float yoff) : yoff{yoff} {}
};

void drawPaddle(GLint &p_draw_loc, GLint &paddle_x_loc, GLint &paddle_y_loc, Paddle &paddle_one, Paddle &paddle_two);
void drawBackdrop(GLint &backdrop_program, GLuint &backdropVAO, GLint &xoff_light_loc, float &xoff_light);
void drawBallAndLight(float radius, float &xspeed, float &xoff, GLint &program, GLuint &VAO, vector<float> &ballshape);
void updateBallLoc(GLint &xoff_loc, float &xoff);
void movePaddle(GLFWwindow * window, Paddle &paddle_one, Paddle &paddle_two);

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

    GLint xoff_u_loc = glGetUniformLocation(program,"xoff");
    float xoff = 0.0f;


                                                            // HANDLING PADDLE OBJECTS
    float paddle_height = 0.4f;
    float paddle_width = 0.05f;

    float paddle_height_buf = paddle_height / 2.0f;
    float paddle_width_buf = paddle_width / 2.0f;
 
    vector<float> paddle = {
        -paddle_width_buf,-paddle_height_buf,
        paddle_width_buf,-paddle_height_buf,
        -paddle_width_buf,paddle_height_buf,
        
        paddle_width_buf, -paddle_height_buf,
        paddle_width_buf, paddle_height_buf,
        -paddle_width_buf,paddle_height_buf 
    };

                                                    // CREATING PADDLES
    GLuint paddleVBO = ogl::genbindVBO();
    ogl::upload_point_enable_AB(1,2,paddle);


                                                    // FETCHING PADDLE UNIFORM LOCATIONS
    GLint paddle_y_loc = glGetUniformLocation(program,"paddle_yoff");
    GLint p_draw_loc = glGetUniformLocation(program,"drawpaddle");
    GLint paddle_x_loc = glGetUniformLocation(program,"paddle_xoff");

    
    glUseProgram(program);                          // UPDATING PADDLE UNIFORMS
    glUniform1f(paddle_y_loc,0.2f);
    glUniform1f(paddle_x_loc,0.2f);
    glUniform1i(p_draw_loc,0);
    glUniform1f(xoff_u_loc,xoff);
    

    vector<float> backdrop = ogl::generateBackdrop();
    GLuint backdropVAO = ogl::genbindVAO();
    GLuint backdropVBO = ogl::genbindVBO();
    ogl::upload_point_enable_AB(0,3,backdrop);
    GLuint vshad_bdrop = ogl::createShader(ogl::VERTEX_SHADER,ogl::loadShaderSource("backshader_vert.glsl").data());
    GLuint fshad_bdrop = ogl::createShader(ogl::FRAGMENT_SHADER,ogl::loadShaderSource("backshader_frag.glsl").data());
    GLint backdrop_progam = ogl::finishProgram(vshad_bdrop,fshad_bdrop);

    GLint xoff_light_loc = glGetUniformLocation(backdrop_progam,"xoffnew");
    glUniform1f(xoff_light_loc,xoff);

    ogl::framecb(window);

    float xspeed = 0.01f;
   

    Paddle paddle_one(0.0f);
    Paddle paddle_two(0.0f);

    while (!glfwWindowShouldClose(window))    
    {
        ogl::setColor(0.2f,0.2f,0.2f,1.0f);

        drawBackdrop(backdrop_progam,backdropVAO,xoff_light_loc,xoff);

        drawBallAndLight(radius,xspeed,xoff,program,VAO,ballshape);
        updateBallLoc(xoff_u_loc,xoff);
      

        drawPaddle(p_draw_loc,paddle_x_loc,paddle_y_loc,paddle_one,paddle_two);
        movePaddle(window, paddle_one, paddle_two);

        ogl::basicEvents(window);
    }

    ogl::cleanUp(window);
}

void drawBackdrop(GLint &backdrop_program, GLuint &backdropVAO, GLint &xoff_light_loc, float &xoff_light) {         // UPDATES LIGHT IN BACKDROP FSHADER
        glUseProgram(backdrop_program);
        glBindVertexArray(backdropVAO);
        glDrawArrays(GL_TRIANGLES,0,6);
        glUniform1f(xoff_light_loc,xoff_light);
}

void drawPaddle(GLint &p_draw_loc, GLint &paddle_x_loc, GLint &paddle_y_loc, Paddle &paddle_one, Paddle &paddle_two) {
        glUniform1i(p_draw_loc,1);

        glDisableVertexAttribArray(0);      // DRAW RIGHT PADDLE
        glUniform1f(paddle_x_loc,0.9f);
        glUniform1f(paddle_y_loc,paddle_two.yoff);
        glDrawArrays(GL_TRIANGLES,0,6);


        glUniform1f(paddle_x_loc,-0.9f);    // DRAW LEFT PADDLE
        glUniform1f(paddle_y_loc,paddle_one.yoff);
        glDrawArrays(GL_TRIANGLES,0,6);
        glEnableVertexAttribArray(0);

        glUniform1i(p_draw_loc,0);
}

void movePaddle(GLFWwindow * window, Paddle &paddle_one, Paddle &paddle_two) {      // PADDLE MOVE & WINDOW COLLISION DETECtION
    if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
        if (paddle_two.yoff < Paddle::paddle_upper_boundary)
            paddle_two.yoff += Paddle::paddle_speed;
        else paddle_two.yoff = Paddle::paddle_upper_boundary;
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (paddle_two.yoff > Paddle::paddle_lower_boundary)
        paddle_two.yoff -= Paddle::paddle_speed;
        else paddle_two.yoff = Paddle::paddle_lower_boundary;
    }
    if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
        if (paddle_one.yoff < Paddle::paddle_upper_boundary)
            paddle_one.yoff += Paddle::paddle_speed;
        else paddle_one.yoff = Paddle::paddle_upper_boundary;
    }
    if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
        if (paddle_one.yoff > Paddle::paddle_lower_boundary)
        paddle_one.yoff -= Paddle::paddle_speed;
        else paddle_one.yoff = Paddle::paddle_lower_boundary;
    }
}

void drawBallAndLight(float radius, float &xspeed, float &xoff, GLint &program, GLuint &VAO, vector<float> &ballshape) {
        glUseProgram(program);
        glBindVertexArray(VAO);
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

        glDrawArrays(GL_TRIANGLE_FAN,0,ballshape.size()/2);
}

void updateBallLoc(GLint &xoff_loc, float &xoff) {
        glUniform1f(xoff_loc,xoff); // update xposition uniform
}