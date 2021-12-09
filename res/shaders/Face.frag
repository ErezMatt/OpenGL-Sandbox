
#version 330

in vec4 vCol;
in vec3 FragPos;

out vec4 color;

uniform vec3 resolution;

float plot(vec2 uv, float pct)
{
return  smoothstep(pct - 0.05, pct, uv.y) - smoothstep(pct, pct + 0.05, uv.y);
}

float hearth(vec2 uv, float size, float blur, vec2 pos)
{
    float distance = size - length(vec2(uv.x + pos.x, uv.y + pos.y- abs(uv.x + pos.x)));
    return smoothstep(0.0, blur, distance);
}

float circle(vec2 uv, float size, float blur, vec2 pos)
{
    float diuvance = size - length(vec2(uv.x + pos.x, uv.y + pos.y));
    return   smoothstep(0.0, blur, diuvance);
}

float mounth(vec2 uv, float size, float blur, vec2 pos, float smile)
{
    float diuvance = size - length(vec2(uv.x + pos.x, uv.y + pos.y));
    float circle1 =  smoothstep(0.0, blur, diuvance);

    float diuvance2 = size - length(vec2(uv.x + pos.x, uv.y + pos.y + smile));
    float circle2 =  smoothstep(0.0, blur, diuvance2);

    return max(circle1 - circle2, 0);
}

void main()
{
    vec2 uv = (FragPos.xy - resolution.xy * 0.5) / min(resolution.x, resolution.y) * 4.0;

    vec3 col =  vec3( circle(uv, 1, 0.005, vec2(0, 0))) * vec3(1.0, 1.0, 0.0);
    col +=    vec3( hearth(uv, 0.15, 0.005, vec2(-0.35, -0.35))) * vec3(0.0, -0.60, 0.9);
    col +=    vec3( hearth(uv, 0.15, 0.005, vec2(0.35, -0.35))) * vec3(0.0, -0.60, 0.9);
    col +=    vec3( mounth(uv, 0.6, 0.005, vec2(0.0, 0.15), -0.2)) * vec3(1.0, -1.0, 0.0);
    color = vec4(col, 1.0);
}