#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Mesh.h"

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intinsity, GLfloat dIntensity);

	void setColor(glm::vec3 newColor) { color = newColor; }
	void setAmbientIntensity(GLfloat newIntensity) { intensity = newIntensity; }
	void setDiffuseIntensity(GLfloat newIntensity) { diffuseIntensity = newIntensity; }

	glm::vec3 getColor() const { return color; }
	GLfloat getAmbientIntensity() const { return intensity; }
	GLfloat getDiffuseIntensity() const { return diffuseIntensity; }

	~Light();

	static void calculateAverageNormals(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

protected:
	glm::vec3 color;
	GLfloat intensity;

	GLfloat diffuseIntensity;
};