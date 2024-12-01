
#include <iostream>
#include <vector>

#include "../includes/oglhelper.h"          // CUSTOM OGL FUNCTIONS
#include "../includes/specific_forwards.h"   

int main()
{

    ogl::init();                                                                // BASIC OGL SETUP START
    GLFWwindow * window = ogl::window(WINDOW_WIDTH_M,WINDOW_HEIGHT_M,"SIMPLE");
    glfwWindowHint(GLFW_SAMPLES,4);
    ogl::setcontext(window);
    ogl::loadglad(window);                                                      // BASIC OGL SETUP END 

    GLuint vertex_array_object = ogl::genbindVAO();                             // GEN AND BIND VAO

                                                                                // GEN ALL SHADERS
    GLuint vertex_shader = ogl::createShader(ogl::VERTEX_SHADER, ogl::loadShaderSource("../shaders/vertex_shader.glsl").data());
    GLuint fragment_shader = ogl::createShader(ogl::FRAGMENT_SHADER, ogl::loadShaderSource("../shaders/fragment_shader.glsl").data());
    GLint shader_program = ogl::finishProgram(vertex_shader, fragment_shader);

    GLint fragment_color_location = glGetUniformLocation(shader_program,"shape_color"); // FRAGMENT SHADER COLOR LOCATION


    GLuint vertex_buffer_backdrop = ogl::genbindVBO();                          // BACKDROP BUFFER
    std::vector<float> backdrop_vertices = ogl::generateBackdrop();
    const GLuint backdrop_array_index = 0;
    ogl::upload_point_enable_AB(backdrop_array_index,3,backdrop_vertices);
    GLint backdrop_boolean_location = glGetUniformLocation(shader_program,"draw_backdrop");

    Ball ball_object;                                                           // BALL OBJECT

    GLuint vertex_buffer_ball = ogl::genbindVBO();                              // BALL BUFFER
    std::vector<float> ball_vertices = ogl::generateBall(Ball::vertex_number,Ball::ball_radius);
    const GLuint ball_array_index = 1;
    ogl::upload_point_enable_AB(ball_array_index,2,ball_vertices);

                                                                                // BALL UNIFORM LOCATIONS
    GLint ball_boolean_location = glGetUniformLocation(shader_program,"draw_ball");
    GLint ball_vec2_location = glGetUniformLocation(shader_program, "ball_offset");

    Paddle paddle_one(-0.94f,0.0f);                                                    // PADDLE OBJECT CREATION
    Paddle paddle_two(0.94f,0.0f);

    GLuint paddle_buffer_object = ogl::genbindVBO();                            // PADDLE BUFFER OBJECT
    std::vector<float> paddle_vertices = {
        -Paddle::paddle_width_ndc, -Paddle::paddle_height_ndc,
        Paddle::paddle_width_ndc, -Paddle::paddle_height_ndc,
        Paddle::paddle_width_ndc, Paddle::paddle_height_ndc,

        -Paddle::paddle_width_ndc, -Paddle::paddle_height_ndc,
        -Paddle::paddle_width_ndc, Paddle::paddle_height_ndc,
        Paddle::paddle_width_ndc, Paddle::paddle_height_ndc,
    };
    const GLuint paddle_array_index = 2;
    ogl::upload_point_enable_AB(paddle_array_index,2,paddle_vertices);

    GLint paddle_boolean_location = glGetUniformLocation(shader_program,"draw_paddle"); // PADDLE LOCATION FETCHING
    GLuint paddle_vec2_location = glGetUniformLocation(shader_program,"paddle_offset");
    glUniform2f(paddle_vec2_location,0.5f,0.5f);

    

    glUseProgram(shader_program);
    glBindVertexArray(vertex_array_object);

    glEnable(GL_MULTISAMPLE);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))                                      // MAIN GAME LOOP START
    {
        ogl::setColor(0.1f,0.1f,0.1f,1.0f);

        drawBackdrop(backdrop_boolean_location,backdrop_array_index,fragment_color_location);                                 

        checkCollision(paddle_one,paddle_two,ball_object);

        moveBall(ball_vec2_location,ball_object);

        drawBall(ball_boolean_location,ball_array_index,fragment_color_location);    

        movePaddles(window, paddle_one, paddle_two);
        
        drawPaddles(paddle_boolean_location,paddle_array_index,fragment_color_location,paddle_vec2_location,paddle_one,paddle_two);



        ogl::basicEvents(window);
    }                                                                           // MAIN GAME LOOP END

    ogl::cleanUp(window);

    return 0;
}

void drawBackdrop(GLint &backdrop_boolean_location, GLuint backdrop_array_index,GLuint fragment_color_location) {
    glEnableVertexAttribArray(backdrop_array_index);
    glUniform1i(backdrop_boolean_location,1);
    glUniform4f(fragment_color_location,0.0f,0.6f,0.8f,1.0f);
    glDrawArrays(GL_TRIANGLES,0,6);
    glUniform1i(backdrop_boolean_location,0);
    glDisableVertexAttribArray(backdrop_array_index);
}

void moveBall(GLint &ball_vec2_location, Ball &ball_object) {
    ball_object.moveball();
    glUniform2f(ball_vec2_location,ball_object.x,ball_object.y);
}

void drawBall(GLint &ball_boolean_location, GLuint ball_array_index, GLuint fragment_color_location) {
    glEnableVertexAttribArray(ball_array_index);
    glUniform1i(ball_boolean_location,1);
    glUniform4f(fragment_color_location,0.2f,0.2f,0.8f,1.0f);
    glDrawArrays(GL_TRIANGLE_FAN,0,Ball::draw_number);
    glUniform1i(ball_boolean_location,0);
    glDisableVertexAttribArray(ball_array_index);
}

void drawPaddles(GLint &paddle_boolean_location, GLuint paddle_array_index, GLuint fragment_color_location, GLuint &paddle_vec2_location, Paddle &paddle_one, Paddle &paddle_two) {
    glEnableVertexAttribArray(paddle_array_index);
    glUniform1i(paddle_boolean_location,1);
    glUniform4f(fragment_color_location,1.0f,1.0f,1.0f,1.0f);
                                                            // PADDLE ONE DRAW
    glUniform2f(paddle_vec2_location,paddle_one.x_offset,paddle_one.y_offset);
    glDrawArrays(GL_TRIANGLES,0,6);
                                                            // PADDLE TWO DRAW
    glUniform2f(paddle_vec2_location,paddle_two.x_offset,paddle_two.y_offset);
    glDrawArrays(GL_TRIANGLES,0,6);

    glUniform1i(paddle_boolean_location,0);
    glDisableVertexAttribArray(paddle_array_index);
}

void movePaddles(GLFWwindow * window, Paddle &paddle_one, Paddle &paddle_two) {      // PADDLE MOVE & WINDOW COLLISION DETECtION
    if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
        if (paddle_two.y_offset < Paddle::paddle_upper_boundary)
            paddle_two.y_offset += Paddle::paddle_speed;
        else paddle_two.y_offset = Paddle::paddle_upper_boundary;
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (paddle_two.y_offset > Paddle::paddle_lower_boundary)
        paddle_two.y_offset -= Paddle::paddle_speed;
        else paddle_two.y_offset = Paddle::paddle_lower_boundary;
    }
    if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
        if (paddle_one.y_offset < Paddle::paddle_upper_boundary)
            paddle_one.y_offset += Paddle::paddle_speed;
        else paddle_one.y_offset = Paddle::paddle_upper_boundary;
    }
    if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
        if (paddle_one.y_offset > Paddle::paddle_lower_boundary)
        paddle_one.y_offset -= Paddle::paddle_speed;
        else paddle_one.y_offset = Paddle::paddle_lower_boundary;
    }
}

void checkCollision(Paddle &paddle_one, Paddle &paddle_two, Ball &ball_object) {
    float paddle_one_lower = paddle_one.y_offset - paddle_one.paddle_height_ndc;
    float paddle_one_upper = paddle_one.y_offset + paddle_one.paddle_height_ndc;

    float paddle_one_right = paddle_one.x_offset + paddle_one.paddle_width_ndc;
    float paddle_one_left = paddle_one.x_offset - paddle_one.paddle_width_ndc;

    float paddle_two_lower = paddle_two.y_offset - paddle_two.paddle_height_ndc;
    float paddle_two_upper = paddle_two.y_offset + paddle_two.paddle_height_ndc;

    float paddle_two_right = paddle_two.x_offset + paddle_two.paddle_width_ndc;
    float paddle_two_left = paddle_two.x_offset - paddle_two.paddle_width_ndc;


    float ball_upper_y = ball_object.y + ball_object.ball_radius;
    float ball_lower_y = ball_object.y - ball_object.ball_radius;
    float ball_left_x = ball_object.x - ball_object.ball_radius;
    float ball_right_x = ball_object.x + ball_object.ball_radius;

    if (ball_left_x < paddle_one_right &&
        ball_right_x > paddle_one_left &&
        ball_lower_y < paddle_one_upper && 
        ball_upper_y > paddle_one_lower) {
            ball_object.speedx *= -1;
            float ydiff = paddle_one.y_offset - ball_lower_y;
            ball_object.speedy += (ydiff / 1000000.0f);
        }
 
    if (ball_left_x < paddle_two_left &&
        ball_right_x > paddle_two_left &&
        ball_lower_y < paddle_two_upper && 
        ball_upper_y > paddle_two_lower) {
            ball_object.speedx *= -1;
            float ydiff = paddle_one.y_offset - ball_lower_y;
            ball_object.speedy += (ydiff / 1000000.0f);
        }
    
}