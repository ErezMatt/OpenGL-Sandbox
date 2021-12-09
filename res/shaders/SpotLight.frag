#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

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

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform sampler2D Texture;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

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

vec4 setPointLight(PointLight pointLight)
{
	vec3 direction = FragPos - pointLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color = LightByDirection(pointLight.base, direction);
	float atteunation = pointLight.exponent * distance * distance + pointLight.linear * distance + pointLight.constant;
		
	return (color / atteunation);
}

vec4 setSpotLight(SpotLight spotLight)
{
	vec3 rDirection = normalize(FragPos - spotLight.base.position);
	float sFactor = dot(rDirection, spotLight.direction);

	if(sFactor > spotLight.edge)
	{
		vec4 color = setPointLight(spotLight.base);
		
		return color * (1.0 - (1.0 - sFactor) * (1.0 / (1.0 - spotLight.edge)));
	}
	else
	{
		return vec4(0, 0, 0, 0);
	}
}


vec4 setSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i = 0; i < spotLightCount; i++)
	{
		totalColor += setSpotLight(spotLights[i]);
	}

	return totalColor;
}

vec4 setPointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{
		totalColor += setPointLight(pointLights[i]);
	}

	return totalColor;
}

void main()
{
	vec4 finalColor = setDirectionalLight();
	finalColor += setPointLights();
	finalColor += setSpotLights();

	color = texture(Texture, TexCoord) * finalColor;
}