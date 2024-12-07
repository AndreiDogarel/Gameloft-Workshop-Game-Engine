#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include <string>
#include <vector>


struct TextureResource {
	std::string filePath;
	std::string fileName;
	std::string type;
	int id;
	GLenum min_filter;
	GLenum mag_filter;
	GLenum wrap_s;
	GLenum wrap_t;
};


class Texture
{
private:
	TextureResource* tr;
	GLuint textureId;

public:
	Texture(TextureResource*); // Constructor
	~Texture(); // Destructor

	// Methods
	void Load();
};

