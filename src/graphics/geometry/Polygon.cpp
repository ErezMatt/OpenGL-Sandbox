#include "Polygon.h"
#include<iostream>
Polygon::Polygon()
{
}

Polygon::Polygon(float x, float y, float radius, int vertexNumber):
    cX{ x },
    cY{ y },
    r{ radius }
{
   
    vertices = {
        {glm::vec3(cX, cY, 0.0f), glm::vec2(0.0f, 0.0f)}
    };


    for (int i = 0; i < vertexNumber; i++)
    {
        double theta = glm::radians(360 / double(vertexNumber) * i);

        double x = radius * cos(theta);
        double y = radius * sin(theta);

        Vertex newV;
        newV.position = glm::vec3(x + cX, y + cY, 0.0f);
        newV.texCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(newV);

        if (i == 0)
            continue;

        indices.push_back(0);
        indices.push_back(vertices.size() - 1);
        indices.push_back(vertices.size() - 2);
    }


    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(vertices.size() - 1);

    mesh.create(vertices, indices);
}

Polygon::~Polygon()
{
    mesh.clear();
}

void Polygon::render()
{
    mesh.render();
}

void Polygon::clear()
{
    mesh.clear();
}
