#include "PointLight.h"

PointLight::PointLight() :
    Light(),
    position{ glm::vec3(0.0f, 0.0f, 0.0f) }
{
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntinsity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat exp, GLfloat lin, GLfloat con):
    Light(red, green, blue, aIntinsity, dIntensity),
    position{ glm::vec3(xPos, yPos, zPos) },
    exponent{ exp },
    linear{ lin },
    constant{ con }
{
}

PointLight::~PointLight()
{
}