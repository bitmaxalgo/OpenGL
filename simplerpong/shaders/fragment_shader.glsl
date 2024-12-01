
#version 330 core

layout (location = 0) out vec4 frag_color;

uniform vec4 shape_color;

void main()
{
    frag_color = vec4(shape_color);
}