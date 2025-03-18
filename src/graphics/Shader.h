#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include <unordered_map>

#include <GL\glew.h>

#include "glm/glm.hpp"

#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	const int MAX_POINT_LIGHTS = 3;
	const int MAX_SPOT_LIGHTS = 3;

public:
	Shader();
	~Shader();

	void createFromString(const std::string& vertexCode, const std::string& fragmentCode);
	void createFromFile(const std::string& vertexLocation, const std::string& fragmentLocation);

	void use() const;
	void unbind() const;
	void clear();

	void SetUniform1i(const std::string& name, int v0);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	void setLight(const Light& light);
	void setDirectionalLight(const DirectionalLight& light);
	void setPointLights(const std::vector<std::unique_ptr<PointLight>> const& pLights);
	void setSpotLights(const std::vector<std::unique_ptr<SpotLight>> const& sLights);

private:
	GLuint shader;
	std::unordered_map<std::string, int> uniformLocationCache;
	
private:
	void create(const std::string& vertexCode, const std::string& fragmentCode);
	void compile(GLuint program, const std::string& shadetCode, GLenum shaderType);
	std::string readFile(const std::string& fileLocation);
	int getUniformLocation(const std::string& name);
};

