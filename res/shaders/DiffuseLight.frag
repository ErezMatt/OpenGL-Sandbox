#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

uniform sampler2D Texture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.base.color, 1.0) * directionalLight.base.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0);
	vec4 diffuseColor = vec4(directionalLight.base.color, 1.0) * directionalLight.base.diffuseIntensity * diffuseFactor;


	color = texture(Texture, TexCoord) * (ambientColour + diffuseColor);
}