#version 330

in vec4 vCol;
in vec3 FragPos;

out vec4 color;

uniform vec3 resolution;

float plot(vec2 uv, float pct)
{
return  smoothstep(pct - 0.05, pct, uv.y) - smoothstep(pct, pct + 0.05, uv.y);
}

void main()
{
    vec2 uv = (FragPos.xy - resolution.xy * 0.5) / min(resolution.x, resolution.y) * 4.0;

    vec3 circleColor = vec3(0.0, 0.40, 0.4);
    float fade = 0.005;
    
    
   
    float distance = 1.0 - length(uv);
    vec3 circle = vec3(smoothstep(0.0, fade, distance));

    color = vec4(circle, 1.0);
    color.rgb *= circleColor;
}