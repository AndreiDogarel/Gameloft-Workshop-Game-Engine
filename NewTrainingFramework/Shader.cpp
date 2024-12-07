#include "stdafx.h"
#include "Shader.h"


Shader::Shader(ShaderResource* _sr) {
	this->sr = _sr;
}

Shader::~Shader() {
	if (this->sr != NULL) {
		delete this->sr;
	}
}

void Shader::Load() {
	char* vertexShader;
	char* fragmentShader;
	strcpy(vertexShader, (*this->sr).filePath.c_str());
	strcat(vertexShader, (*this->sr).vertexShader.c_str());
	strcpy(fragmentShader, (*this->sr).filePath.c_str());
	strcat(fragmentShader, (*this->sr).vertexShader.c_str());

	Shaders* shader = new Shaders();
	this->shaderId = (*shader).Init(vertexShader, fragmentShader);
}