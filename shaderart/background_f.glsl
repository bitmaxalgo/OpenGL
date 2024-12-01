#version 330 core

layout (location = 0) out vec4 fragColor;

uniform vec2 resolution;
uniform float time;

vec3 palette( float t ) {

    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b*cos( 6.28318*(c*t+d) );

}

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution.xy * 2.0 - 1.0;
    uv.x *= resolution.x / resolution.y;

    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);


    for (float i = 0.0; i < 2.0; i ++) {

        uv *= 2.0;
        uv = fract(uv);
        uv -= 0.5;

        float d = length(uv);

        vec3 col = palette(length(uv0) + time);

        d = sin(d*8. + time)/8.;    
        d = abs(d);

        d = 0.02 / d;

        finalColor += col * d;
    }
    fragColor = vec4(finalColor,1.0f);
}