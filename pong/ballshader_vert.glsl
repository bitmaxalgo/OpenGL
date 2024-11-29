
#version 330 core                           // VERT SHADER THAT HANDLES BALL & PADDLE POSITION

layout (location = 0) in vec2 ballposition;
layout (location = 1) in vec2 paddleposition;

uniform float xoff;

uniform bool drawpaddle;
uniform float paddle_yoff;
uniform float paddle_xoff;


void main()
{
    if (!drawpaddle) {
        vec2 copy = ballposition;
        copy.x += xoff;
        gl_Position = vec4(copy.x,copy.y,0.0f,1.0f); 
    }

    if (drawpaddle) {
        vec2 copy = paddleposition;
        copy.y += paddle_yoff;
        copy.x += paddle_xoff;
        gl_Position = vec4(copy.x,copy.y,0.0f,1.0f);        
    }
}