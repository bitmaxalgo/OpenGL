#version 330 core

layout (location = 0) in vec2 ballposition;
out vec4 color;

void main()
{
    vec2 copy = ballposition;
    gl_Position = vec4(copy.x,copy.y,0.0f,1.0f); 
    color = vec4(1.0f,0.0f,0.0f,1.0f);
}