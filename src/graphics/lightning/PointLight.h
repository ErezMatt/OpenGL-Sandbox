#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat intinsity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat exponent, GLfloat linear, GLfloat constant);
	~PointLight();

	void setPosition(glm::vec3 newPosition) { position = newPosition; }
	void setExponent(GLfloat newExponent) { exponent = newExponent; }
	void setLinear(GLfloat newLinear) { linear = newLinear; }
	void setConstant(GLfloat newConstant) { constant = newConstant; }

	glm::vec3 getPosition() const { return position; }
	GLfloat getExponent() const { return exponent; }
	GLfloat getLinear() const { return linear; }
	GLfloat getConstant() const { return constant; }

protected:
	glm::vec3 position;

	GLfloat exponent{ 0.0f };
	GLfloat linear{ 0.0f };
	GLfloat constant{ 1.0f };
};

