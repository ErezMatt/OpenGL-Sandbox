#pragma once
#include "Mesh.h"
#include <memory>
class Sphere
{
public:
    Sphere();
    Sphere(float x, float y, float z, float radius, int stacks, int sectors);
    ~Sphere();

    void render();
    void clear();

private:
    Mesh mesh;

    float cX;
    float cY;
    float cZ;
    float r;
    std::vector<unsigned int> indices;
    std::vector <Vertex> vertices;
};

