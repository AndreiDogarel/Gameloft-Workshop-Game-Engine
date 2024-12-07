#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include <string>
#include <vector>
#include "Shaders.h"

struct ShaderResource {
	std::string filePath;
	int id;
	std::string vertexShader;
	std::string fragmentShader;
};


class Shader
{
private:
	ShaderResource* sr;
	GLuint shaderId;

public:
	Shader(ShaderResource*);
	~Shader();

	// Methods
	void Load();
};

