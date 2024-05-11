#pragma once

#include <GL\glew.h>

#include <string>

class Texture
{
public:
	enum class Format { RGB, RGBA };

public:
	explicit Texture(const std::string& fileLocation = "");
	// Delete copy constructor & copy assignment
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other) noexcept;            
	Texture& operator=(Texture&& other) noexcept; 

	bool load(Format format = Format::RGBA);
	void use(unsigned int slot = 0);
	void clear();

	~Texture();

private:
	GLuint textureID;
	int width;
	int height;
	int bitDepth;

	std::string fileLocation;
};