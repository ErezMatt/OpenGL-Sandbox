#version 330

in vec4 vCol;
in vec3 FragPos;

out vec4 color;

uniform vec3 resolution;
uniform float time;

void main()
{
    vec2 uv = (FragPos.xy - resolution.xy * 0.5) / min(resolution.x, resolution.y) * 4.0;
  
    vec3 circleColor = 0.5 + 0.5*cos(time+uv.xyx + vec3(0, 2, 4));
    uv.y -= sqrt(abs(uv.x));
    float fade = 0.005;
    
   
    float diuvance = 1.0 - length(uv);
    vec3 circle = vec3(smoothstep(0.0, fade, diuvance)) * circleColor;

    color = vec4(circle, 1.0);
}