#include "SpotLight.h"

SpotLight::SpotLight(): 
	PointLight(),
	direction{ glm::vec3(0.0f, 0.0f, 0.0f) },
	edge{ 0.0f },
	calculationEdge{ 1.0f }
{
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntinsity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat exponent, GLfloat linear, GLfloat constant, GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat angle):
	PointLight(red, green, blue, aIntinsity, dIntensity, xPos, yPos, zPos, exponent, linear, constant),
	direction{ glm::normalize(glm::vec3(xDirection, yDirection, zDirection)) },
	edge{ angle },
	calculationEdge{ cosf(glm::radians(angle)) }
{
}

void SpotLight::setRay(glm::vec3 newPosition, glm::vec3 newDirection)
{
	position = newPosition;
	direction = newDirection;
}

SpotLight::~SpotLight()
{
}
