#ifdef GL_ES
precision mediump float;
#endif

//uniform float u_time;
uniform vec2 u_resolution;

uniform sampler2D u_screen;

const float RAYCAST_QUALITY = 100.0;

vec3 raycast(vec2 pos, vec2 coord)
{
    vec2 step = vec2(0.0);
    vec2 dir = normalize(coord - pos) / RAYCAST_QUALITY;
    vec3 res = vec3(1.0);
    vec4 point;

    //if (texture2D(u_screen, coord).r > 0.0)
       //return (1.0);
    for (float i = 0.0; i < RAYCAST_QUALITY; i++){
        point = texture2D(u_screen, step + coord);
        res *= point.rgb + (1.0 - length(point.rgb)) * 0.99;
        if (point.r > 0.0)
           break;
        step += dir;
    }
    return (res);
}

float terrain(vec2 p)
{
    return (mix(0.95, 1.0, step(0.25, texture2D(u_screen, 0.0625 + p / 2.0).r)));
}

void main()
{
    vec2 p = gl_FragCoord.xy / u_resolution;
    vec2 pos = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);

    vec2 l = vec2(0.5, 0.5);
    vec2 d = p - l;
    float b = 1.0;
    float t = 0.0;
    for(float i = 0.0; i < RAYCAST_QUALITY; i++) {
        t -= 1.0 / RAYCAST_QUALITY;
        b *= 1.0 - texture2D(u_screen, p + d * t).r;
    }

    b *= 0.05 / length(pos);
    vec4 res = vec4(b);
    res += texture2D(u_screen, p);
    //b *= 1.0 - smoothstep(0.0, 0.5, length(d));
    gl_FragColor = res;
}

void old_main()
{
    vec2 coord = gl_FragCoord.xy / u_resolution;
    vec2 pos = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
    float len = 0.0;

    len += 0.1 / length(pos);
    vec3 res = vec3(len) * raycast(vec2(0.5), coord);
    res += texture2D(u_screen, coord).xyz;
    gl_FragColor = vec4(res, 1.0);
}
