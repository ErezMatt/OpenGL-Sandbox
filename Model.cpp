#include "Model.h"

#include <filesystem>

Model::Model()
{
}

Model::~Model()
{
	clear();
}

bool Model::load(const std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene) {
		std::cerr << "Model failed to load: " << filePath << std::endl;
		return false;
	}

	loadNode(scene->mRootNode, scene);

	std::string textureDir = (std::filesystem::path(filePath).parent_path() / std::filesystem::path("Textures/")).string();
	loadMaterials(scene, textureDir);

	return true;
}

void Model::render()
{
	for (const auto& meshData : meshList) {
		if (meshData.textureIndex < textureList.size())
			textureList[meshData.textureIndex]->use();

		meshData.mesh->render();
	}
}

void Model::clear()
{
	meshList.clear();
	textureList.clear();
}

void Model::loadNode(const aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; ++i) {
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; ++i) {
		loadNode(node->mChildren[i], scene);
	}
}

void Model::loadMesh(const aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);
	std::vector<unsigned int> indices;
	indices.reserve(mesh->mNumFaces * 3);

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex newV;
		newV.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		newV.texCoords = mesh->HasTextureCoords(0) ?
					     glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)
						 : glm::vec2(0.0f, 0.0f);
		newV.normals = glm::vec3(-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z);
		vertices.push_back(newV);
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	auto newMesh = std::make_unique<Mesh>(vertices, indices);
	meshList.emplace_back(MeshData{ std::move(newMesh), mesh->mMaterialIndex });
}

void Model::loadMaterials(const aiScene* scene, const std::string& textureDirPath)
{
	textureList.reserve(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		bool textureLoaded = false;
		aiMaterial* material = scene->mMaterials[i];

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				std::string filename = std::filesystem::path(path.data).filename().string();
				std::string texturePath = (std::filesystem::path(textureDirPath) / filename).string();

				auto newTexture = std::make_unique<Texture>(texturePath);

				if (!newTexture->load(Texture::Format::RGB)) {
					std::cout << "Failed to load texture: " << texturePath << std::endl;
				}
				else {
					textureList.push_back(std::move(newTexture));
					textureLoaded = true;
				}
			}
		}

		if (!textureLoaded) {
			auto newTexture = std::make_unique<Texture>("res/textures/plain.png");
			newTexture->load();
			textureList.push_back(std::move(newTexture));
			
		}
	}
}