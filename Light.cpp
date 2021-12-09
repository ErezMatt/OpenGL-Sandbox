#include "Light.h"

Light::Light() :
	color{ glm::vec3(1.0f, 1.0f, 1.0f) },
	intensity{ 1.0f },
	diffuseIntensity{0.0f}
{
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity) :
	color{ glm::vec3(red, green, blue) },
	intensity{ aIntensity },
	diffuseIntensity{ dIntensity }
{
}

Light::~Light()
{
}

void Light::calculateAverageNormals(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        if (i + 2 > indices.size())
            return;

        unsigned int in0 = indices[i + 0];
        unsigned int in1 = indices[i + 1];
        unsigned int in2 = indices[i + 2];

        glm::vec3 v1(vertices[in1].position - vertices[in0].position);
        glm::vec3 v2(vertices[in2].position - vertices[in0].position);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        vertices[in0].normals += normal;
        vertices[in1].normals += normal;
        vertices[in2].normals += normal;
    }

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        glm::vec3 vec = vertices[i].normals;
        vec = glm::normalize(vec);
        vertices[i].normals = glm::normalize(vertices[i].normals);
    }
}
