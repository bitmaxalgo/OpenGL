
#version 330 core

out vec4 fcolor;
uniform float xoffnew;

vec4 test = vec4(400.0f,300.0f,0.0f,1.0f);

void main() {
    float fragoff = 400.0f + xoffnew * 400.0f;
    test.x = fragoff;
    float intensity = 100 / length(test - gl_FragCoord);
    fcolor = vec4(0.0f,0.2f,0.2f,1.0f) * intensity;
}
