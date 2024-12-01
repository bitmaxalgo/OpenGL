
#version 330 core

layout (location = 0) in vec2 pointposition;

void main()
{
    gl_Position = vec4(pointposition,0.0f,1.0f);    
}