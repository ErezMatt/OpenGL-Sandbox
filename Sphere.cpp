#include "Sphere.h"
#include "Light.h"

Sphere::Sphere()
{
}

Sphere::Sphere(float x, float y, float z, float radius, int stacks, int sectors):
	cX{ x },
	cY{ y },
	cZ{ z },
	r{ radius }
{
    float radiusInv = 1.0f / radius;

    std::vector<unsigned int> indices = {
    };

    std::vector <Vertex> vertices = {
        {
            glm::vec3(cX, cY + radius , cZ),
            glm::vec2(0.5f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f)
        },
    };

 
    for (int j = 0; j < stacks; j++)
    {
        for (int i = 0; i <=sectors; i++)
        {
            double theta = glm::radians((360 / double(sectors)) * i);
            double alfa = glm::radians(90 - (180 / double(stacks)) * j);

            double x = radius * cos(alfa) * cos(theta);
            double y = radius * sin(alfa);
            double z = radius * cos(alfa) * sin(theta);

            Vertex newV;
            newV.position = glm::vec3(x + cX, y + cY, z + cZ);
            newV.texCoords = glm::vec2(i / double(sectors+1), j / double(stacks));
            newV.normals = glm::vec3(-(x - cX) * radiusInv, -(y - cY) * radiusInv, -(z - cZ) * radiusInv);
            vertices.push_back(newV);
        }
    }

    Vertex bottom;
    bottom.position = glm::vec3(cX, cY - radius, cZ);
    bottom.texCoords = glm::vec2(0.5f, 1.0f);
    bottom.normals = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices.push_back(bottom);


    for (int j = 1; j < stacks; j++)
    {
        for (int i = 0; i <= sectors; i++)
        {
            indices.push_back((j - 1) * (sectors+1) + i);
            indices.push_back((j)* (sectors + 1) + i);
            indices.push_back((j - 1) * (sectors + 1) + i + 1);

            indices.push_back((j - 1) * (sectors + 1) + i + 1);
            indices.push_back((j)* (sectors + 1) + i);
            indices.push_back((j)* (sectors + 1) + i + 1);
        }

    }

    for (int i = 1; i <=sectors; i++)
    {
        indices.push_back((stacks - 1) * (sectors + 1) + i);
        indices.push_back(vertices.size() - 1);
        indices.push_back((stacks - 1) * (sectors + 1) + i + 1);
    }


    mesh.create(vertices, indices);
}

Sphere::~Sphere()
{
}

void Sphere::render()
{
	mesh.render();
}

void Sphere::clear()
{
	mesh.clear();
}
