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
    uv.y -= sqrt(abs(uv.x));
    vec3 circleColor = vec3(1.0, 0.40, 0.9);
    float fade = 0.005;
    
    
   
    float distance = 1.0 - length(uv);
    vec3 col = vec3(smoothstep(0.0, fade, distance)) * circleColor;

    color = vec4(col, 1.0);
}