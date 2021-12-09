#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight();
	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat intinsity, GLfloat dIntensity, 
		GLfloat xPos, GLfloat yPos, GLfloat zPos, 
		GLfloat exponent, GLfloat linear, GLfloat constant,
		GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,
		GLfloat ang);

	void setDirection(glm::vec3 newDirection) { direction = newDirection; }
	void setEdge(GLfloat newEdge) { edge = newEdge; }
	void setCalculationEdge(GLfloat newCalculationEdge) { calculationEdge = newCalculationEdge; }
	void setRay(glm::vec3 newPosition, glm::vec3 newDirection);

	glm::vec3 getDirection() const { return direction; }
	GLfloat getEdge() const { return edge; }
	GLfloat getCalculationEdge() const { return calculationEdge; }

	~SpotLight();

private:
	glm::vec3 direction;

	GLfloat edge;
	GLfloat calculationEdge;
};

