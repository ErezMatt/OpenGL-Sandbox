#include "DirectionalLight.h"

DirectionalLight::DirectionalLight():
	Light(),
	direction{ glm::vec3(0.0f, 0.0f, 0.0f) }
{
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntinsity, GLfloat dIntensity, GLfloat xDirection, GLfloat yDirection, GLfloat zDirection):
	Light(red, green, blue, aIntinsity, dIntensity),
	direction{ glm::vec3(xDirection, yDirection, zDirection) }

{
}

DirectionalLight::~DirectionalLight()
{
}

