#pragma once

#include <GL\glew.h>

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	Model(Model&&) noexcept = default;
	Model& operator=(Model&&) noexcept = default;

	bool load(const std::string& fileLocation);
	void render();
	void clear();

	~Model();

private:
	struct MeshData {
		std::unique_ptr<Mesh> mesh;
		size_t textureIndex;
	};
	std::vector<MeshData> meshList;
	std::vector<std::unique_ptr<Texture>> textureList;
	//std::vector<unsigned int> meshTextureID;

private:
	void loadNode(const aiNode* node, const aiScene* scene);
	void loadMesh(const aiMesh* mesh, const aiScene* scene);
	void loadMaterials(const aiScene* scene, const std::string& textureDirPath);
};