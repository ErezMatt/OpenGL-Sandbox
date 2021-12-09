#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 projection;

void main()
{
   gl_Position = projection * model * vec4(pos, 1.0);
   vCol = vec4(clamp(pos, 0.0, 1.0), 1.0);

   FragPos = (model * vec4(pos, 1.0)).xyz;
}