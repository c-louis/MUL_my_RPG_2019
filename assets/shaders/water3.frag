#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

void main()
{
    vec2 pos = 6.0 * gl_FragCoord.xy / u_resolution;

    for (int i = 1; i < 8; i++){
        float c = float(i);

        pos.x += 0.7 / c * sin(pos.y + u_time / 10000.0 + 0.3) + 0.8;
        pos.y += 0.4 / c * sin(pos.x + u_time / 10000.0 + 0.3) + 1.6;
    }
    gl_FragColor = vec4(0.5 * sin(pos.x) + 0.5, 0.5 * sin(pos.y) + 0.5, sin(pos.x + pos.y), 1.0);
}