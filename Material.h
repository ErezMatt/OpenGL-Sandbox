#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>

#include <vector>

#include "Shader.h"
#include "Camera.h"

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat sShininess);

	void use(Shader& shader);


	~Material();

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

