
#version 330 core                           // FRAG SHADER FOR LIGHT BEHIND BALL

out vec4 fcolor;
uniform float xoffnew;

vec4 test = vec4(400.0f,300.0f,0.0f,1.0f);

void main() {
    float fragoff = 400.0f + xoffnew * 400.0f;
    test.x = fragoff;
    float intensity = 40 / length(test - gl_FragCoord);
    fcolor = vec4(1.0f,0.6f,0.8f,1.0f) * intensity;
}
