#version 330 core

layout (location = 0) in vec2 position;

void main()
{
    vec2 copyposition = position;
    copyposition.xy += 0.2f;
    gl_Position = vec4(copyposition, 0.0f, 1.0f);
}