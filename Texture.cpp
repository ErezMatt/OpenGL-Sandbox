#include "Texture.h"

#include <iostream>

#include "stb_image.h"

Texture::Texture(const std::string& fileLocation) :
	textureID{0},
	width{0},
	height{0},
	bitDepth{0},
	fileLocation{fileLocation}
{
}

Texture::Texture(Texture&& other) noexcept :
	textureID(other.textureID),
	width(other.width), 
	height(other.height),
	bitDepth(other.bitDepth), 
	fileLocation(std::move(other.fileLocation)) 
{
	other.textureID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if (this != &other) {
		clear();
		textureID = other.textureID;
		width = other.width;
		height = other.height;
		bitDepth = other.bitDepth;
		fileLocation = std::move(other.fileLocation);
		other.textureID = 0;
	}
	return *this;
}

bool Texture::load(Format format)
{
	clear();

	int channels = (format == Format::RGBA) ? 4 : 3;
	unsigned char* textureBuffer = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, channels);
	if (!textureBuffer) {
		std::cerr << "ERROR: Failed to load texture: " << fileLocation << std::endl;
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum glFormat = (format == Format::RGBA) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, textureBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (textureBuffer)
		stbi_image_free(textureBuffer);

	return true;
}

void Texture::use(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clear()
{	
	if (textureID) {
		glDeleteTextures(1, &textureID);
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
		fileLocation.clear();
	}
}

Texture::~Texture()
{
	clear();
}