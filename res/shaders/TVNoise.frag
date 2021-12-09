#version 330

in vec4 vCol;
in vec3 FragPos;

out vec4 color;

uniform vec3 resolution;
uniform float time;

void main()
{
    vec2 uv = (FragPos.xy - resolution.xy * 0.5) / min(resolution.x, resolution.y) * 4.0;
  
    float c = fract(sin(uv.x*100+uv.y)*10000*time);
    vec3 col = vec3(c);

    color = vec4(col, 1.0);
}