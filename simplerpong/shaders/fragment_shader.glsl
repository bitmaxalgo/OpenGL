
#version 330 core

layout (location = 0) out vec4 frag_color;

uniform vec4 shape_color;
uniform vec2 resolution;

void main()
{
    vec2 uv = (gl_FragCoord.xy / resolution) * 2.0 - 1.0;
    float aspect_ratio = resolution.x / resolution.y;

    uv.x *= aspect_ratio;

    frag_color = vec4(shape_color);
}