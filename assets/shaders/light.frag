#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

void main()
{
    vec2 pos = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
    float len = 0.0;

    len += 0.1 * 0.1 / length(pos);
    gl_FragColor = vec4(vec3(sin(u_time / 10000.0)), 1.0);
}