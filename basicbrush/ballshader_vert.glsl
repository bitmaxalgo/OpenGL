#version 330 core

layout (location = 0) in vec2 ballposition;
uniform float xpos;
uniform float ypos;

void main()
{
    vec2 copy = ballposition;
    copy.x += xpos;
    copy.y -= ypos;
    gl_Position = vec4(copy.x,copy.y,0.0f,1.0f); 
}