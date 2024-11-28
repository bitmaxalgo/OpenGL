#version 330 core

layout (location = 0) in vec2 ballposition;
out vec4 color;

void main()
{
    gl_Position = vec4(ballposition,0.0f,1.0f); 
    color = vec4(1.0f,0.0f,1.0f,1.0f);
}