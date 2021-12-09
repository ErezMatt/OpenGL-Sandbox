#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntinsity, GLfloat dIntensity, GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);

	~DirectionalLight();

	void setDirection(glm::vec3 newDirection) { direction = newDirection; }
	glm::vec3 getDiection() const { return direction; }


private:
	glm::vec3 direction;

};

