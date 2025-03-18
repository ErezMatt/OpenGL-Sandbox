#pragma once
#include "Mesh.h"
#include <memory>

class Polygon
{
public:
    Polygon();
    Polygon(float x, float y, float radius, int num_segments);
    ~Polygon();

    void render();
    void clear();

private:
    Mesh mesh;

    float cX;
    float cY;
    float r;
    std::vector<unsigned int> indices;
    std::vector <Vertex> vertices;
};

