#pragma once

#include <GL\glew.h>

#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& fileLocation);

	bool load();
	bool loadNoAlfa();
	void use();
	void clear();

	~Texture();

private:
	GLuint textureID;
	int width;
	int height;
	int bitDepth;

	std::string fileLocation;
};