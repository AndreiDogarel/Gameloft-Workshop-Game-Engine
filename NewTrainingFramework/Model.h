#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include <string>
#include <vector>


struct ModelResource {
	std::string filePath;
	std::string fileName;
	int id;
};


class Model
{
private:
	ModelResource* mr;
	GLuint iboId;
	GLuint wiredIboId;
	GLuint vboId;
	int nrIndici;
	int nrVertecsi;
	int nrIndiciWired;

public:
	Model(ModelResource*); // Constructor
	~Model(); // Destructor

	// Methods
	void Load();
};

