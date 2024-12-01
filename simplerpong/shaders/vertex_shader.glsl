
#version 330 core

layout (location = 0) in vec3 backdrop_vertices;        // BACKDROP DRAW
uniform bool draw_backdrop;


layout (location = 1) in vec2 ball_vertices;            // BALL DRAW
uniform bool draw_ball;

uniform vec2 ball_offset;                               // BALL MOVEMENT


layout (location = 2) in vec2 paddle_vertices;            // PADDLE DRAW
uniform bool draw_paddle;

uniform vec2 paddle_offset;                               // PADDLE OFFSET


layout (location = 3) in vec2 zero_vertices;
uniform bool draw_zero;                             // DRAW ZERO

uniform vec2 resolution;

vec2 processBallMovements();                            // FORWARD DECLARATION

void main()
{
    float aspect_ratio = resolution.x / resolution.y;
    if (draw_backdrop)
    {
        vec3 backdrop_vertices_copy = backdrop_vertices;
        backdrop_vertices_copy.x /= aspect_ratio;
        gl_Position = vec4(backdrop_vertices_copy,1.0f);
    }
    else if (draw_ball)
    {
        vec2 ball_updated_position = processBallMovements();
        ball_updated_position.x /= aspect_ratio;
        gl_Position = vec4(ball_updated_position,0.0f,1.0f);

    }
    else if (draw_paddle)
    {
        vec2 paddle_vertices_copy = paddle_vertices;
        paddle_vertices_copy += paddle_offset;
        paddle_vertices_copy.x /= aspect_ratio;
        gl_Position = vec4(paddle_vertices_copy,0.0f,1.0f);        

    }
    else if (draw_zero)
    {
        vec2 zero_vertices_copy = zero_vertices;
        gl_Position = vec4(zero_vertices_copy,0.0f,1.0f);
    }
}

vec2 processBallMovements() 
{
    vec2 ball_vertices_copy = ball_vertices;
    ball_vertices_copy += ball_offset;
    return ball_vertices_copy;
}