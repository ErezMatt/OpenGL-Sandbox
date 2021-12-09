#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

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


struct Material
{
	float specularIntensity;
	float shininess;
};

uniform sampler2D Texture;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 cameraPosition;

void main()
{
	vec4 ambientColour = vec4(directionalLight.base.color, 1.0) * directionalLight.base.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0);
	vec4 diffuseColor = vec4(directionalLight.base.color, 1.0) * directionalLight.base.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0, 0, 0, 0);

	if(diffuseFactor > 0.0)
	{
		vec3 fragCamera = normalize(cameraPosition - FragPos);
		vec3 reflected = normalize(reflect(directionalLight.direction, normalize(Normal)));

		float specularFactor = dot(fragCamera, reflected);
		if(specularFactor > 0.0)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(directionalLight.base.color * material.specularIntensity * specularFactor, 1.0);
		}
	}

	color = (ambientColour + diffuseColor + specularColor) * vec4(0.5, 0.5, 0.5, 1);
}