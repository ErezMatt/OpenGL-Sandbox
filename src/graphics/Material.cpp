#include "Material.h"

Material::Material():
	specularIntensity{ 0.0f },
	shininess{ 0.0f }
{
}

Material::Material(GLfloat sIntensity, GLfloat sShininess):
	specularIntensity{ sIntensity },
	shininess{ sShininess }
{
}

void Material::use(Shader& shader)
{
	shader.SetUniform1f("material.specularIntensity", specularIntensity);
	shader.SetUniform1f("material.shininess", shininess);
}

Material::~Material()
{
}
