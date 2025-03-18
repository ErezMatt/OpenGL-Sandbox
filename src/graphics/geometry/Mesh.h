#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 texCoords = glm::vec2(0.0f, 0.0f);
	glm::vec3 normals = glm::vec3(0.0f, 0.0f, 0.0f);
};

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	void create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void render();
	void clear();

private:
	GLuint vao, vbo, ibo;
	GLsizei indexCount;
};

