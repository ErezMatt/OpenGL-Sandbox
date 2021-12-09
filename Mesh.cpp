#include "Mesh.h"

Mesh::Mesh():
	vao{ 0 },
	vbo{ 0 },
	ibo{ 0 },
	indexCount{ 0 }
{
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
    vao{ 0 },
    vbo{ 0 },
    ibo{ 0 },
    indexCount{ 0 }
{
    create(vertices, indices);
}

Mesh::~Mesh()
{
    clear();
}

void Mesh::create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	indexCount = indices.size();
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexCount, &indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));
    glEnableVertexAttribArray(1); 
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normals)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::render()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::clear()
{
    if (ibo != 0)
        glDeleteBuffers(1, &ibo);

    if (vbo != 0)
        glDeleteBuffers(1, &vbo);

    if (vao != 0)
        glDeleteVertexArrays(1, &vao);

    indexCount = 0;
}
