#version 330

in vec2 TexCoord;

out vec4 color;

struct Light
{
	vec3 color;
	float ambientIntensity;
};

uniform sampler2D Texture;
uniform Light light;

void main()
{
	vec4 ambientColour = vec4(light.color, 1.0f) * light.ambientIntensity;
	color = texture(Texture, TexCoord) * ambientColour;
}