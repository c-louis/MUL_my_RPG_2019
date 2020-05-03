#ifdef GL_ES
precision mediump float;
#endif

uniform vec3 u_color;
uniform vec2 u_resolution;
uniform int u_size;

void main()
{
    vec2 p = gl_FragCoord.xy / u_resolution;
    vec2 pos = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
    float future = float(u_size) * 0.001 / length(pos);
    
    gl_FragColor = vec4(u_color * future, future);
}
