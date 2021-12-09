#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;

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

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;

uniform sampler2D Texture;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform Material material;

uniform vec3 cameraPosition;

vec4 LightByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.color, 1.0) * light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0);
	vec4 diffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0, 0, 0, 0);

	if(diffuseFactor > 0.0)
	{
		vec3 fragCamera = normalize(cameraPosition - FragPos);
		vec3 reflected = normalize(reflect(direction, normalize(Normal)));

		float specularFactor = dot(fragCamera, reflected);
		if(specularFactor > 0.0)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0);
		}
	}

	return (ambientColour + diffuseColor + specularColor);
}

vec4 setDirectionalLight()
{
	return LightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 PointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{
		vec3 direction = FragPos - pointLights[i].position;
		float distance = length(direction);
		direction = normalize(direction);

		vec4 color = LightByDirection(pointLights[i].base, direction);
		float atteunation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
		
		totalColor += (color / atteunation);
	}

	return totalColor;
}

void main()
{
	vec4 finalColor = setDirectionalLight();
	finalColor += PointLights();
	color = texture(Texture, TexCoord) * finalColor;
}